//
// Created by js on 31/08/22.
//

#ifndef __THEORY_FOR_LOOPS_H__
#define __THEORY_FOR_LOOPS_H__

#include "../../generalized_domain.h"
#include "../../instructions/instruction.h"
#include "../../instructions/for.h"
#include "../../instructions/end_for.h"

namespace theory::core {
    class Fors {
    public:
        Fors() = default;

        ~Fors() = default;

        static void make_fors(GeneralizedDomain *gd, int modifier){
            /// For Inc instructions consist of 2 instructions, FOR and ENDFOR, and at least requires some instruction
            /// in between while respecting the END instruction in the last line, e.g.
            /// [from]. FOR(pointer--); [from-1]. ... ; [from-x=to].ENDFOR; ... [y in [to+1,_program_lines)]. END
            auto v_pointers = gd->get_pointers();
            auto program_lines = gd->get_program_lines();
            for(const auto& ptr : v_pointers) {
                for(size_t dest_line=program_lines-2; dest_line > 1; dest_line--){
                //for(size_t dest_line=2u; dest_line + 2 < program_lines; dest_line++){
                    // FOR(ptr++) or FOR(ptr--)
                    auto for_mod = std::make_unique<instructions::For>(ptr,dest_line,modifier);
                    gd->add_instruction(std::move(for_mod));

                }
                for (size_t start_line = 0; start_line < program_lines - 3; start_line++) {
                    // ENDFOR(ptr++) or ENDFOR(ptr--)
                    auto endfor_inc = std::make_unique<instructions::EndFor>(ptr, start_line, modifier);
                    gd->add_instruction(std::move(endfor_inc));
                }
            }
        }
    };
}

#endif //__THEORY_FOR_LOOPS_H__
