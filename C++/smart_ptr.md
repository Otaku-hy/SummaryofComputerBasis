智能指针种类：unique_ptr / shared_ptr / weak_ptr

使用RAII思想解决动态分配内存时的内存泄露问题，当智能指针释放时会隐式的释放系统为其分配的空间（如果使用普通指针管理则还需要自己手动释放）

设计原则：在栈上的分配智能指针

1. unique_ptr

   unique_ptr设计成独占式的，即unique_ptr拥有它所管理的对象的所有权且不和其他对象共享。因此，unique_ptr的拷贝相关的运算符被删除。想要传递资源所有权需要使用移动相关的运算符，并使用std::move语义。

   简单实现:

   ```c++
   #include <iostream>
   #include <utility>
   
   struct Data
   {
       int a;
       int b;
       Data(int a,int b) : a(a), b(b) {}; 
   };
   
   template<typename T>
   class UniquePtr
   {
   private:
       T* mpData;
   public:
       UniquePtr(T* pData = nullptr) : mpData(pData) {};
   
       UniquePtr(const UniquePtr& other) = delete;
       UniquePtr& operator=(const UniquePtr& other) = delete;
   
       UniquePtr(UniquePtr&& other) : mpData(other.mpData){
           other.mpData = nullptr;
       };
       UniquePtr& operator=(UniquePtr&& other){
           if(this != &other){
               if(mpData) delete[] mpData;
               this->mpData = other.mpData;
               other.mpData = nullptr;
           }
           return *this;
       }
   
       ~UniquePtr(){
           if(mpData) delete[] mpData;
           mpData = nullptr;
       }
   
       T* get() const {
           return mpData;
       }
       T* operator->() const {
           return mpData;
       }
       T& operator*() const {
           return *this;
       }
   };
   
   template<typename T,typename ...Args>
   UniquePtr<T> make_shared(Args &&...args)
   {
       return UniquePtr<T>(new T(std::forward<Args>(args)...));
   }
   
   int main()
   {
       auto p = make_shared<Data>(1,2);
       std::cout << p.get();
   }
   ```

​	**注：当一个函数不需要资源的控制权限时，可以只传给函数一个普通指针。于是unique_ptr多和ptr同时出现

2. shared_ptr

​	unique_ptr解决重复释放的方式是禁止拷贝，这样导致使用较麻烦；shared_ptr使用引用计数的方式使得资源的控制权限被多个指针共有。

​	**引用计数并不是类静态变量也不是每个类都不同的成员变量，所以要把计数放在堆区，可以使多个指针/线程共同访问：在操作计数的函数中还需要加锁保证正确性

简单实现：

```c++
#include <iostream>
#include <utility>
#include <memory>
#include <mutex>

template <typename T>
class SharedPtr
{
private:
    std::mutex *mpLock;
    int *mpCount;
    T *mpData;

public:
    SharedPtr(T *pData) : mpData(pData), mpCount(new int(1)), mpLock(new std::mutex()){};
    SharedPtr(const SharedPtr &other) {
        mpCount = other.mpCount;
        mpData = other.mpData;
        mpLock = other.mpLock;
        mpLock->lock();
        (*mpCount)++;
        mpLock->unlock();
    }
    SharedPtr(SharedPtr &&other) {
        mpCount = other.mpCount;
        mpData = other.mpData;
        mpLock = other.mpLock;
        other.mpCount = nullptr;
        other.mpLock = nullptr;
        other.mpData = nullptr;
    }

    SharedPtr &operator=(const SharedPtr &other) {
        ~SharedPtr();
        mpLock = other.mpLock;
        mpData = other.mpData;
        mpCount = other.mpCount;
        mpLock->lock();
        (*mpCount)++;
        mpLock->unlock();
    }

    SharedPtr &operator=(SharedPtr &&other) {
        ~SharedPtr();
        mpLock = other.mpLock;
        mpData = other.mpData;
        mpCount = other.mpCount;
        other.mpCount = nullptr;
        other.mpLock = nullptr;
        other.mpData = nullptr;
    }

    ~SharedPtr() {
        if(!mpLock) return;
        mpLock->lock();
        int result = (*mpCount)--;
        mpLock->unlock();
        if (result == 0)
        {
            delete mpLock;
            delete mpCount;
            if(mpData)
                delete mpData;
            mpData = nullptr;
        }
    }

    int use_count() const {
        return *mpCount;
    }

    T* get() const {
        return mpData;
    }

    T* operator->() const {
        return mpData;
    }

    T& operator*() const {
        return *mpData;
    }
};

template<typename T,typename ...Args>
SharedPtr<T> make_shared(Args &&...args)
{
    return SharedPtr<T>(new T(std::forward(args)...));
}

int main()
{
    int* p = new int(1);
    SharedPtr<int> sp(p);
    auto pp = sp;
    std::cout << pp.use_count();
}
```

**注：shared_ptr的引用计数是可以互斥访问的，但是它指向的对象的无锁。

3. weak_ptr

   当我们有些指针不拥有资源控制权限，即不影响引用计数，所以引入了weak_ptr。

   但是，为了并发访问时的正确访问，weak_ptr也提供lock函数生成一个shared_ptr，使得在访问期间对象资源无法被删除掉，影响访问。

​	**在可能出现多个智能指针相互管控交错的资源时，可能会导致死锁而无法回收资源，所以要求在这种情况下weak_ptr和shared_ptr共用来防止死锁。