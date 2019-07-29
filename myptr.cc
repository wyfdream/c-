#include<iostream>
using namespace std;
template<class T>
class myshare_ptr
{
public:

	myshare_ptr(T* p) :m_count(new int), ptr(p) {}
	myshare_ptr& operator=(const myshare_ptr& p)
	{
		--*m_count;
		if (*m_count == 0)
			delete p;
		ptr = p;
		++*p.m_count;
		m_count = p.m_count;
	}
	T* operator->()
	{
		return ptr;
	}
	T& operator*()
	{
		return *ptr;
	}
	~myshare_ptr()
	{
		--*m_count;
		if (*m_count == 0)
		{
			delete m_count;
			delete ptr;
			m_count = nullptr;
			ptr = nullptr;
		}
	}
private:
	int* m_count;
	T* ptr;
};

//采用仿函数定义删除器
class Delete
{
public:
	template<class T>
	void operator()(T* p)const
	{
		delete p;
	}
};
template<class T,class D=Delete>
class myunique_ptr
{
public:
	explicit myunique_ptr(T* pp=nullptr,const D& dd=D())
		:un_ptr(pp),del(dd){}
	~myunique_ptr()
	{
		del(un_ptr);
	}
	myunique_ptr(const myunique_ptr&) = delete;
	myunique_ptr& operator=(const myunique_ptr&) = delete;
	myunique_ptr(myunique_ptr&& right_value) :
		un_ptr(right_value.un_ptr), del(std::move(right_value.del)) {
		right_value.un_ptr = nullptr;
	}
	myunique_ptr& operator=(myunique_ptr&& right_value) noexcept {
		if (this != &right_value) {
			std::cout << "operator && right_value " << std::endl;
			del(*this);
			un_ptr = right_value.un_ptr;
			del = std::move(right_value.del);
			right_value.un_ptr = nullptr;
		}
		return *this;
	}
	T* release() {
		T *tmp = un_ptr;
		un_ptr = nullptr;
		return  tmp;
	}
	void reset() { del(un_ptr); }
	void reset(T* q) {
		if (un_ptr) {
			del(un_ptr);
			un_ptr = q;
		}
		else
			un_ptr = nullptr;
	}
	void swap(unique_ptr &other) noexcept {
		using std::swap;
		swap(un_ptr, other.un_ptr);
		swap(del, other.del);
	}
	T* get() { return un_ptr; }
	D& get_deleter() { return  del; }
	T& operator*() { return *un_ptr; }//*
	T* operator->() { return  un_ptr; }//->
private:
	T* un_ptr = nullptr;
	D del;
};

typedef struct
{
	int x;
	int y;
}block;
int main()
{
	myshare_ptr<block> my(new block());
	my->x = 2;
	my->y = 3;
	cout << (*my).x << "  " << (*my).y << endl;
	return 0;
}
