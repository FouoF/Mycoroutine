#ifndef _MYCOROUTINE_NONCOPYABLE_H
#define _MYCOROUTINE_NONCOPYABLE_H

namespace mycoroutine
{
class noncopyable
{
private:
  noncopyable(const noncopyable&) = delete;
  noncopyable(const noncopyable&&) = delete;
  void operator=(const noncopyable&) = delete;
protected:
  noncopyable() = default;
  ~noncopyable() = default;
};

}

#endif