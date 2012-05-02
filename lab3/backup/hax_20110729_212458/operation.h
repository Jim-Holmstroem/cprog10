#ifndef OPERATION_H
#define OPERATION_H

namespace hax{
    class Level;
    class Character;

    class Operation{
      public:
        virtual void call(const std::string arg, Character* curChar, Level* curLevel) = 0;
    };
    class LevelOpVoid : public Operation{
      private:
        typedef void(Level::*FcnPtr)(void);
        FcnPtr op;
      protected:
      public:
//      Level* curLevel;
        LevelOpVoid(){};
        LevelOpVoid(FcnPtr op){
//          this->curLevel = curLevel;
            this->op = op;
        };
        virtual void call(const std::string arg, Character* curChar, Level* curLevel){
            (curLevel->*op)();
        };
    };
    class LevelOpBool1String : public Operation{
      public:
        typedef bool(Level::*FcnPtr)(std::string);
        FcnPtr op;
        LevelOpBool1String(FcnPtr op){
//          this->curLevel = curLevel;
            this->op = op;
        };
        void call(const std::string arg, Character* curChar, Level* curLevel){
            if(arg == ""){
                std::cout << "Specify a target" << std::endl;
            }else{
                (curLevel->*op)(arg);
            }
        };
    };



    class CharOp : public Operation{
      public:
        virtual void call(const std::string arg, Character* curChar, Level* curLevel) = 0;
    };
    class CharOpVoid : public CharOp{
      public:
        typedef void(Character::*FcnPtr)(void);
        FcnPtr op;
        CharOpVoid(FcnPtr op){
            this->op = op;
        };
        void call(const std::string arg, Character* curChar, Level* curLevel){
            if(curChar != NULL){
                (curChar->*op)();
            }else{
                std::cout <<"No focused character" << std::endl;
            };
        };
    };
    class CharOpBoolVoid : public CharOp{
      public:
        typedef bool(Character::*FcnPtr)(void);
        FcnPtr op;
        CharOpBoolVoid(FcnPtr op){
            this->op = op;
        };
        void call(const std::string arg, Character* curChar, Level* curLevel){
            if(curChar != NULL){
                (curChar->*op)();
            }else{
                std::cout <<"No focused character" << std::endl;
            };
        };
    };
    class CharOpBool1String : public CharOp{
      public:
        typedef bool(Character::*FcnPtr)(std::string);
        FcnPtr op;
        CharOpBool1String(FcnPtr op){
            this->op = op;
        };
        void call(const std::string arg, Character* curChar, Level* curLevel){
            if(curChar != NULL){
                if(arg == ""){
                    std::cout << "Specify a target" << std::endl;
                }else{
                    (curChar->*op)(arg);
                }
            }else{
                std::cout << "No focused character" << std::endl;
            }
        };
    };

}
#endif
