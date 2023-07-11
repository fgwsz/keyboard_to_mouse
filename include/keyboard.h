#pragma once
#include<string>
#include<Windows.h>
#include<unordered_map>

class KeyBoard{
public:
    // 将输入的键盘按键值转化为按键名称
    static ::std::string const& keyCodeToName(DWORD key_code);
private:
    static ::std::unordered_map<DWORD,::std::string> key_code_to_name_map_;
};

enum KeyCode{

    KeyCode_A='A',
    KeyCode_B='B',
    KeyCode_C='C',
    KeyCode_D='D',
    KeyCode_E='E',
    KeyCode_F='F',
    KeyCode_G='G',
    KeyCode_H='H',
    KeyCode_I='I',
    KeyCode_J='J',
    KeyCode_K='K',
    KeyCode_L='L',
    KeyCode_M='M',
    KeyCode_N='N',
    KeyCode_O='O',
    KeyCode_P='P',
    KeyCode_Q='Q',
    KeyCode_R='R',
    KeyCode_S='S',
    KeyCode_T='T',
    KeyCode_U='U',
    KeyCode_V='V',
    KeyCode_W='W',
    KeyCode_X='X',
    KeyCode_Y='Y',
    KeyCode_Z='Z',

    KeyCode_0='0',
    KeyCode_1='1',
    KeyCode_2='2',
    KeyCode_3='3',
    KeyCode_4='4',
    KeyCode_5='5',
    KeyCode_6='6',
    KeyCode_7='7',
    KeyCode_8='8',
    KeyCode_9='9',

    KeyCode_Backspace         =8  ,
    KeyCode_Tab               =9  ,
    KeyCode_Enter             =13 ,
    KeyCode_PauseBreak        =19 ,
    KeyCode_CapsLk            =20 ,
    KeyCode_Esc               =27 ,
    KeyCode_Space             =32 ,
    KeyCode_PageUp            =33 ,
    KeyCode_PageDown          =34 ,
    KeyCode_End               =35 ,
    KeyCode_Home              =36 ,
    KeyCode_Left              =37 ,
    KeyCode_Up                =38 ,
    KeyCode_Right             =39 ,
    KeyCode_Down              =40 ,
    KeyCode_PrintScreen       =44 ,
    KeyCode_Insert            =45 ,
    KeyCode_Delete            =46 ,
    KeyCode_LeftWin           =91 ,
    KeyCode_RightWin          =92 ,
    KeyCode_Application       =93 ,
    KeyCode_Multiply          =106,// Operator*
    KeyCode_Plus              =107,// Operator+
    KeyCode_Minus             =109,// Operator-
    KeyCode_Divide            =111,// Operator/
    KeyCode_F1                =112,
    KeyCode_F2                =113,
    KeyCode_F3                =114,
    KeyCode_F4                =115,
    KeyCode_F5                =116,
    KeyCode_F6                =117,
    KeyCode_F7                =118,
    KeyCode_F8                =119,
    KeyCode_F9                =120,
    KeyCode_F10               =121,
    KeyCode_F11               =122,
    KeyCode_F12               =123,
    KeyCode_NumLock           =144,
    KeyCode_ScrollLock        =145,
    KeyCode_LeftShift         =160,
    KeyCode_RightShfit        =161,
    KeyCode_LeftCtrl          =162,
    KeyCode_RightCtrl         =163,
    KeyCode_LeftAlt           =164,
    KeyCode_RightAlt          =165,
    KeyCode_Semicolon         =186,// ;
    KeyCode_Equal             =187,// =
    KeyCode_Comma             =188,// ,
    KeyCode_Hyphen            =189,// -
    KeyCode_Period            =190,// .
    KeyCode_Slash             =191,// /
    KeyCode_BackQuote         =192,// `
    KeyCode_LeftSquareBracket =219,// [
    KeyCode_VerticalBar       =220,// |
    KeyCode_RightSquareBracket=221,// ]
    KeyCode_SingleQuote       =222 // '
};

::std::unordered_map<DWORD,::std::string> KeyBoard::key_code_to_name_map_={

    {KeyCode_A,"A"},
    {KeyCode_B,"B"},
    {KeyCode_C,"C"},
    {KeyCode_D,"D"},
    {KeyCode_E,"E"},
    {KeyCode_F,"F"},
    {KeyCode_G,"G"},
    {KeyCode_H,"H"},
    {KeyCode_I,"I"},
    {KeyCode_J,"J"},
    {KeyCode_K,"K"},
    {KeyCode_L,"L"},
    {KeyCode_M,"M"},
    {KeyCode_N,"N"},
    {KeyCode_O,"O"},
    {KeyCode_P,"P"},
    {KeyCode_Q,"Q"},
    {KeyCode_R,"R"},
    {KeyCode_S,"S"},
    {KeyCode_T,"T"},
    {KeyCode_U,"U"},
    {KeyCode_V,"V"},
    {KeyCode_W,"W"},
    {KeyCode_X,"X"},
    {KeyCode_Y,"Y"},
    {KeyCode_Z,"Z"},

    {KeyCode_0,"0"},
    {KeyCode_1,"1"},
    {KeyCode_2,"2"},
    {KeyCode_3,"3"},
    {KeyCode_4,"4"},
    {KeyCode_5,"5"},
    {KeyCode_6,"6"},
    {KeyCode_7,"7"},
    {KeyCode_8,"8"},
    {KeyCode_9,"9"},

    {KeyCode_Backspace         ,"Backspace"  },
    {KeyCode_Tab               ,"Tab"        },
    {KeyCode_Enter             ,"Enter"      },
    {KeyCode_PauseBreak        ,"PauseBreak" },
    {KeyCode_CapsLk            ,"CapsLk"     },
    {KeyCode_Esc               ,"Esc"        },
    {KeyCode_Space             ,"Space"      },
    {KeyCode_PageUp            ,"PageUp"     },
    {KeyCode_PageDown          ,"PageDown"   },
    {KeyCode_End               ,"End"        },
    {KeyCode_Home              ,"Home"       },
    {KeyCode_Left              ,"Left"       },
    {KeyCode_Up                ,"Up"         },
    {KeyCode_Right             ,"Right"      },
    {KeyCode_Down              ,"Down"       },
    {KeyCode_PrintScreen       ,"PrintScreen"},
    {KeyCode_Insert            ,"Insert"     },
    {KeyCode_Delete            ,"Delete"     },
    {KeyCode_LeftWin           ,"LeftWin"    },
    {KeyCode_RightWin          ,"RightWin"   },
    {KeyCode_Application       ,"Application"},
    {KeyCode_Multiply          ,"Operator*"  },
    {KeyCode_Plus              ,"Operator+"  },
    {KeyCode_Minus             ,"Operator-"  },
    {KeyCode_Divide            ,"Operator/"  },
    {KeyCode_F1                ,"F1"         },
    {KeyCode_F2                ,"F2"         },
    {KeyCode_F3                ,"F3"         },
    {KeyCode_F4                ,"F4"         },
    {KeyCode_F5                ,"F5"         },
    {KeyCode_F6                ,"F6"         },
    {KeyCode_F7                ,"F7"         },
    {KeyCode_F8                ,"F8"         },
    {KeyCode_F9                ,"F9"         },
    {KeyCode_F10               ,"F10"        },
    {KeyCode_F11               ,"F11"        },
    {KeyCode_F12               ,"F12"        },
    {KeyCode_NumLock           ,"NumLock"    },
    {KeyCode_ScrollLock        ,"ScrollLock" },
    {KeyCode_LeftShift         ,"LeftShift"  },
    {KeyCode_RightShfit        ,"RightShfit" },
    {KeyCode_LeftCtrl          ,"LeftCtrl"   },
    {KeyCode_RightCtrl         ,"RightCtrl"  },
    {KeyCode_LeftAlt           ,"LeftAlt"    },
    {KeyCode_RightAlt          ,"RightAlt"   },
    {KeyCode_Semicolon         ,";"          },
    {KeyCode_Equal             ,"="          },
    {KeyCode_Comma             ,","          },
    {KeyCode_Hyphen            ,"-"          },
    {KeyCode_Period            ,"."          },
    {KeyCode_Slash             ,"/"          },
    {KeyCode_BackQuote         ,"`"          },
    {KeyCode_LeftSquareBracket ,"["          },
    {KeyCode_VerticalBar       ,"|"          },
    {KeyCode_RightSquareBracket,"]"          },
    {KeyCode_SingleQuote       ,"\'"         }
};

::std::string const& KeyBoard::keyCodeToName(DWORD key_code){
    if(KeyBoard::key_code_to_name_map_.count(key_code)==0){
        KeyBoard::key_code_to_name_map_.emplace(key_code,::std::to_string(key_code));
    }
    return KeyBoard::key_code_to_name_map_.at(key_code);
}
