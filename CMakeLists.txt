cmake_minimum_required(VERSION 3.14)
project(Matrix)

#set(CMAKE_CXX_COMPILER "/usr/bin/clang++" CACHE string "clang compiler" FORCE) #TODO check if clang is present when COVERAGE needed
                

set(CMAKE_CXX_STANDART 20)
set(CMAKE_CXX_STANDART_REQUIRED ON)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -pthread" CACHE STRING "Comment" FORCE)

set(CMAKE_CXX_FLAGS_NTHREADS_RELEASE   "${CMAKE_CXX_FLAGS} -D NTHREADS -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_NTHREADS_SANITIZER "${CMAKE_CXX_FLAGS} -D NTHREADS -Wpedantic -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_NTHREADS_COVERAGE  "${CMAKE_CXX_FLAGS} -D NTHREADS -D NDEBUG -fprofile-instr-generate -fcoverage-mapping" CACHE STRING "Comment" FORCE)

set(CMAKE_CXX_FLAGS_RELEASE   "${CMAKE_CXX_FLAGS} -D NDEBUG" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_SANITIZER "${CMAKE_CXX_FLAGS} -Wpedantic -Wall -Wextra -Wformat=2 -fsanitize=address,undefined -g" CACHE STRING "Comment" FORCE)
set(CMAKE_CXX_FLAGS_COVERAGE  "${CMAKE_CXX_FLAGS} -D NDEBUG -fprofile-instr-generate -fcoverage-mapping" CACHE STRING "Comment" FORCE)

set(CMAKE_CXX_FLAGS_ALL_ERRORS "${CMAKE_CXX_FLAGS} -g -Werror -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wmissing-declarations -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-check -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr -lm -pie")

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.8.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


set_target_properties(gtest PROPERTIES FOLDER extern)
set_target_properties(gtest_main PROPERTIES FOLDER extern)
set_target_properties(gmock PROPERTIES FOLDER extern)
set_target_properties(gmock_main PROPERTIES FOLDER extern)

enable_testing()


add_subdirectory(./tests)


message("")
message("")
message("")
message("                                                                                                                                                       ")
message("                                                                                                                   .,                                  ")
message("                                                                                                                 ,((((,                                ")
message("                                                                                                  /@@#(, .*//////%@&%#/.                               ")
message("                                                                                               ..,&%%@@*@#///********/#/.                              ")
message("                                                                                        ..,//##((#&&%#@@//#((***********/##/,..                        ")
message("                                                                                      *//****/(((/%@##@&@/**********************/(.                    ")
message("                                                                                  .,//********/(//(&(#%(/******//////************/%(                   ")
message("                                                  .***/*.                     .*/(/*************/##(*****************//*************#%/.               ")
message("                                                      .,((,.   .        ...,*//***********/*******/(***/**/*#%&%&#/***///***/*****/,*//(.              ")
message("                                   .  .,,*,,.,***///*******/((/////(#((///*************************************#&@%%#******************//.             ")
message("                              ,/((**/***((/****************************************************************/**/**************************(*            ")
message("                        .*(((/****///************************************************************************************************//***/#(.         ")
message("                      ,//*************************************/*******************************************************************///////////(*        ")
message("                 .,/(/*******************************************/**************************************************************//////////////(*.      ")
message("              .*(/,.,*******************************************//************************************************************//////////((///(/(*.     ")
message("                 /#(*******************************************/************************************************************/////////(#%%%((##((&*     ")
message("              ,//****************************************************************************/*********/#***/************/**///////////(##%((((#/.     ")
message("           .(/**********************************************//**/**/************************//***********(/****/************/////////((((((((((%,      ")
message("         *#************************************************//**/*****************************************/(&(*******//*****////////(/(((((((((#,       ")
message("       ,(/************************************************//************************************************(((//**/*/////(*/(//////((((((((#(.        ")
message("      (/************************************************///******/********************************************#/#####((((((((((#/(#(((#(((#/           ")
message("    .%/************************************************/////**************************************************/*////(##%%%@@%. ...  ..,.               ")
message("   .(//*********************************/************/(/*//*****************************************************///*/////(#(                           ")
message("   */%/**************************************************/***/*************************************************////((////*.                            ")
message("  .//(****************************/(************************//*************************************************//////*((,                              ")
message("   .**********************/(///***(************************//*************************************************/////*//,                                ")
message("   .(*********************((*/****(/**********************************************************************/(*//**/(/.                                  ")
message("   .&************************/***(//**/**************************/(/********/****************************//((/**//.                                    ")
message("   .%****************************(**(**********************//**////****//**(/**************************/(///*/(*.                                      ")
message("   .(***************************/#///***************/****/****//*/****//**(/**************************##(/*/#,                                         ")
message("   ,(*******************************(*/****************//****//*/****/**/////**********************/##////(.                                           ")
message("   */*************************************************//****((*//**(//***/*******/*///**********/###/(/#,                                              ")
message("   ,/********************************************/***/(/***/(**/*/////***********(/(/*****//*(&&((//(%                                                 ")
message("   ,(**************************************/**/****************//***/************#(*****(##&@%(///#/                                                   ")
message("   .#//***************************************/******************////***********##(((#%@@&%#(#((#*.     .                                              ")
message("    ,* /***********************************//*************//*/////((%**********/%((%@@%%#((((#(,                                                       ")
message("       /**************************************/**/*********///////(%@(*****/**/%&@@@@%##%##%%,                                                         ")
message("       /*****************************************//***////////////#&@#///*/**(%(.#@&&&%(##(,                                                           ")
message("       .(/****************************************/////////////(((#&@@*/////*%/  %@&%&%%%(.                                                            ")
message("         (%#(%#//**********///*/*********/****//////**//////////*/#&@@/*/////#*  ,%&%###(,                                                             ")
message("                     .,...*/***//*/***/*********//**//////(##%%(%#(%%#(//////#* ,*%&#((#*                                                              ")
message("                           .*(/*****/**//////////,..      .....,..  .%////////#..##(((##*                                                              ")
message("                                   .*,.                            ,#///////(//%(##((((#/.                                                             ")
message("                                                                  *(/#(///(/(/(//#%#((((((((/,                                                         ")
message("                                                                 .#/(.*((/#((((#(//(##(//(%&###(.                                                      ")
message("                                                                 .(/, .###%../(((#((##/,  .                                                            ")
message("                                                                       .@((     .*,                                                                    ")
message("")
message("")
message("")
message("\t\t\t\t\t\t\t  ---------------------------------")
message("\t\t\t\t\t\t\t  |  Thx for checking out my lab! |")
message("\t\t\t\t\t\t\t  ---------------------------------")


