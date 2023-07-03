#pragma once
#include<string>
#include<Windows.h>
#include<unordered_map>

class KeyBoard{
public:
    // 将输入的键盘按键值转化为按键名称
    static ::std::string const& keyCodeToName(DWORD key_code);
private:
    static ::std::unordered_map<DWORD,::std::string> _key_code_to_name_map;
    static bool _init_flag;
};

::std::unordered_map<DWORD,::std::string> KeyBoard::_key_code_to_name_map{};

bool KeyBoard::_init_flag=[&](){
    for(DWORD key_code='A';key_code<='Z';++key_code){
        KeyBoard::_key_code_to_name_map.emplace(key_code,::std::string(1,key_code));
    }
    for(DWORD key_code='0';key_code<='9';++key_code){
        KeyBoard::_key_code_to_name_map.emplace(key_code,::std::string(1,key_code));
    }
    KeyBoard::_key_code_to_name_map.emplace(160,"LeftShift"  );
    KeyBoard::_key_code_to_name_map.emplace(161,"RightShfit" );
    KeyBoard::_key_code_to_name_map.emplace(162,"LeftCtrl"   );
    KeyBoard::_key_code_to_name_map.emplace(163,"RightCtrl"  );
    KeyBoard::_key_code_to_name_map.emplace(164,"LeftAlt"    );
    KeyBoard::_key_code_to_name_map.emplace(165,"RightAlt"   );
    KeyBoard::_key_code_to_name_map.emplace(27 ,"Esc"        );
    KeyBoard::_key_code_to_name_map.emplace(9  ,"Tab"        );
    KeyBoard::_key_code_to_name_map.emplace(8  ,"Backspace"  );
    KeyBoard::_key_code_to_name_map.emplace(13 ,"Enter"      );
    KeyBoard::_key_code_to_name_map.emplace(20 ,"CapsLk"     );
    KeyBoard::_key_code_to_name_map.emplace(93 ,"Application");
    KeyBoard::_key_code_to_name_map.emplace(32 ,"Space"      );
    KeyBoard::_key_code_to_name_map.emplace(38 ,"Up"         );
    KeyBoard::_key_code_to_name_map.emplace(40 ,"Down"       );
    KeyBoard::_key_code_to_name_map.emplace(37 ,"Left"       );
    KeyBoard::_key_code_to_name_map.emplace(39 ,"Right"      );
    KeyBoard::_key_code_to_name_map.emplace(91 ,"Win"        );
    KeyBoard::_key_code_to_name_map.emplace(112,"F1"         );
    KeyBoard::_key_code_to_name_map.emplace(113,"F2"         );
    KeyBoard::_key_code_to_name_map.emplace(114,"F3"         );
    KeyBoard::_key_code_to_name_map.emplace(115,"F4"         );
    KeyBoard::_key_code_to_name_map.emplace(116,"F5"         );
    KeyBoard::_key_code_to_name_map.emplace(117,"F6"         );
    KeyBoard::_key_code_to_name_map.emplace(118,"F7"         );
    KeyBoard::_key_code_to_name_map.emplace(119,"F8"         );
    KeyBoard::_key_code_to_name_map.emplace(120,"F9"         );
    KeyBoard::_key_code_to_name_map.emplace(121,"F10"        );
    KeyBoard::_key_code_to_name_map.emplace(122,"F11"        );
    KeyBoard::_key_code_to_name_map.emplace(123,"F12"        );
    KeyBoard::_key_code_to_name_map.emplace(189,"-"          );
    KeyBoard::_key_code_to_name_map.emplace(187,"="          );
    KeyBoard::_key_code_to_name_map.emplace(219,"["          );
    KeyBoard::_key_code_to_name_map.emplace(221,"]"          );
    KeyBoard::_key_code_to_name_map.emplace(220,"|"          );
    KeyBoard::_key_code_to_name_map.emplace(186,";"          );
    KeyBoard::_key_code_to_name_map.emplace(222,"\'"         );
    KeyBoard::_key_code_to_name_map.emplace(188,","          );
    KeyBoard::_key_code_to_name_map.emplace(190,"."          );
    KeyBoard::_key_code_to_name_map.emplace(191,"/"          );
    return true;
}();

::std::string const& KeyBoard::keyCodeToName(DWORD key_code){
    if(KeyBoard::_key_code_to_name_map.count(key_code)==0){
        KeyBoard::_key_code_to_name_map.emplace(key_code,::std::to_string(key_code));
    }
    return KeyBoard::_key_code_to_name_map.at(key_code);
}
