//
// Created by js on 1/09/22.
//

#ifndef __THEORIES_CORE_TERMINAL_H__
#define __THEORIES_CORE_TERMINAL_H__

#include "../../instructions/end.h"
#include "../../generalized_domain.h"

namespace theory::core{
    class Terminal{
        /// The Terminal theory consists of an End instruction that can be programmed in any line
    public:
        Terminal(GeneralizedDomain *gd){
            gd->add_instruction(std::make_unique<instructions::End>());
        }
    };
}

#endif //__THEORIES_CORE_TERMINAL_H__
