#pragma once
#include<iostream>
#include<type_traits>

class Logger{
private:
    static bool global_enable_;
    bool enable_;
    ::std::string head_;
    static bool init_flag_;
public:
    Logger(bool enable,::std::string const& head)
        :enable_(enable)
        ,head_(head)
    {}
    Logger():Logger(true,"")
    {}
    Logger& setEnable(bool enable){ 
        this->enable_=enable;
        return *this;
    }
    Logger& setHead(::std::string const& head){
        this->head_=head;
        return *this;
    }
    static void setGlobalEnable(bool global_enable){
        Logger::global_enable_=global_enable;
    }
private:
    template<typename _Type>
    void _print(_Type&& arg){
        ::std::cout<<::std::forward<_Type>(arg);
    }
    void _print(){}
    template<typename _Type,typename..._Types>
    void _print(_Type&& arg,_Types&&...args){
        this->_print(::std::forward<_Type>(arg));
        if constexpr(sizeof...(args)!=0){
            this->_print(::std::forward<_Types>(args)...);
        }    
    }
    template<typename..._Types>
    void _println(_Types&&...args){
        this->_print(::std::forward<_Types>(args)...);
        this->_print('\n'); 
    }
    static bool _init();
public:
    template<typename..._Types>
    Logger& print(_Types&&...args){
        if(this->global_enable_&&this->enable_){
            this->_print(this->head_);
            this->_print(::std::forward<_Types>(args)...);
        }
        return *this;
    }
    template<typename..._Types>
    Logger& println(_Types&&...args){
        if(this->global_enable_&&this->enable_){
            this->_print(this->head_);
            this->_println(::std::forward<_Types>(args)...);
        }
        return *this;
    }
};

bool Logger::global_enable_=true;

bool Logger::init_flag_=Logger::_init();

bool Logger::_init(){ // 优化::std::cout输出性能
    ::std::ios::sync_with_stdio(false); // 关闭与stdio的同步
    ::std::cout<<::std::unitbuf; // 设置为无缓冲区
    return true;
}
