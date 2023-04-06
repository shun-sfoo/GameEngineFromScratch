#pragma once

#include "Interface.hpp"

namespace My {
Interface IRuntimeModule {
 public:
  // 对于有其他虚函数的类，建议把析构函数也声明为virtual。
  // 这是因为如果不这么做，那么当使用基类指针释放派生类的实例的时候，
  // 可能导致只调用了基类的析构函数，从而产生memory leak的情况。
  virtual ~IRuntimeModule(){};

  virtual int Initialize() = 0;  // 这是用来初始化模块的
  virtual void Finalize() = 0;  // 这是用来在模块结束的时候打扫战场的

  // 这个是用来让驱动模块驱动该模块执行的。每调用一次，模块进行一个单位的处理
  virtual void Tick() = 0;
};

// 之所以要单独定义模块的初始化/反初始化函数，而不是在类的构造函数/析构函数里面完成这些工作，主要是有以下一些考虑：

// 在C/C++当中，全局变量（包括static变量）的初始化顺序是不可预知的（未定义的）。
// 对于不同的平台，可能顺序不同。类当中的成员变量的初始化顺序也有类似的问题
// 有些模块我们可能只是想预加载到内存，后面再初始化。或者有些模块在流程当中可能出现临时不用的情况，
// 想要释放相关的平台资源，但是想保留其状态，并不想将其从内存卸载。

}  // namespace My
