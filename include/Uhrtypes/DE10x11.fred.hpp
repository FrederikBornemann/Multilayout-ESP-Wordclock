#pragma once

#include "Uhrtype.hpp"

/*
 *           Layout Front
 *                COL
 *       X 9 8 7 6 5 4 3 2 1 0
 * ROW + - - - - - - - - - - -
 *  0  | E S K I S T L F Ü N F    113 112 111 110 109 108 107 106 105 104 103
 *  1  | Z E H N Z W A N Z I G    092 093 094 095 096 097 098 099 100 101 102
 *  2  | D R E I V I E R T E L    091 090 089 088 087 086 085 084 083 082 081
 *  3  | T G N A C H V O R J M    070 071 072 073 074 075 076 077 078 079 080
 *  4  | H A L B Q Z W Ö L F P    069 068 067 066 065 064 063 062 061 060 059
 *  5  | Z W E I N S I E B E N    048 049 050 051 052 053 054 055 056 057 058
 *  6  | K D R E I R H F Ü N F    047 046 045 044 043 042 041 040 039 038 037
 *  7  | E L F N E U N V I E R    026 027 028 029 030 031 032 033 034 035 036
 *  8  | W A C H T Z E H N R S    025 024 023 022 021 020 019 018 017 016 015
 *  9  | B S E C H S F M U H R    004 005 006 007 008 009 010 011 012 013 014
 *  X  |     *   *   *   *                003     002     001     000
 */

class De10x11Fred_t : public iUhrType {
public:
    virtual LanguageAbbreviation usedLang() override {
        return LanguageAbbreviation::DE;
    };

    //------------------------------------------------------------------------------

    virtual const bool hasDreiviertel() override { return true; }

    //------------------------------------------------------------------------------

    void show(FrontWord word) override {
        switch (word) {

        case FrontWord::es_ist:
            setFrontMatrixWord(0, 9, 10);
            setFrontMatrixWord(0, 5, 7);
            break;

        case FrontWord::nach:
        case FrontWord::v_nach:
            setFrontMatrixWord(3, 5, 8);
            break;

        case FrontWord::vor:
        case FrontWord::v_vor:
            setFrontMatrixWord(3, 2, 4);
            break;

        case FrontWord::viertel:
            setFrontMatrixWord(2, 0, 6);
            break;

        case FrontWord::dreiviertel:
            setFrontMatrixWord(2, 0, 10);
            break;

        case FrontWord::min_5:
            setFrontMatrixWord(0, 0, 3);
            break;

        case FrontWord::min_10:
            setFrontMatrixWord(1, 7, 10);
            break;

        case FrontWord::min_20:
            setFrontMatrixWord(1, 0, 6);
            break;

        case FrontWord::halb:
            setFrontMatrixWord(4, 7, 10);
            break;

        case FrontWord::eins:
            setFrontMatrixWord(5, 5, 8);
            break;

        case FrontWord::uhr:
            setFrontMatrixWord(9, 0, 2);
            break;

        case FrontWord::hour_1:
            setFrontMatrixWord(5, 6, 8);
            break;

        case FrontWord::hour_2:
            setFrontMatrixWord(5, 7, 10);
            break;

        case FrontWord::hour_3:
            setFrontMatrixWord(6, 6, 9);
            break;

        case FrontWord::hour_4:
            setFrontMatrixWord(7, 0, 3);
            break;

        case FrontWord::hour_5:
            setFrontMatrixWord(6, 0, 3);
            break;

        case FrontWord::hour_6:
            setFrontMatrixWord(9, 5, 9);
            break;

        case FrontWord::hour_7:
            setFrontMatrixWord(5, 0, 5);
            break;

        case FrontWord::hour_8:
            setFrontMatrixWord(8, 6, 9);
            break;

        case FrontWord::hour_9:
            setFrontMatrixWord(7, 4, 7);
            break;

        case FrontWord::hour_10:
            setFrontMatrixWord(8, 2, 5);
            break;

        case FrontWord::hour_11:
            setFrontMatrixWord(7, 8, 10);
            break;

        case FrontWord::hour_12:
            setFrontMatrixWord(4, 1, 5);
            break;

        default:
            break;
        };
    };

    //------------------------------------------------------------------------------

    virtual const uint16_t getFrontMatrixIndex(uint8_t row,
                                               uint8_t col) override {
        uint8_t newColsWordMatrix = colsWordMatrix();
        uint16_t numPixelsWordMatrix = rowsWordMatrix() * colsWordMatrix();

        if (G.buildTypeDef == BuildTypeDef::DoubleResM1) {
            newColsWordMatrix = 2 * colsWordMatrix() - 1;
            numPixelsWordMatrix = rowsWordMatrix() * newColsWordMatrix;
            col *= 2;
        }
        if (row % 2 != 0) {
            col = newColsWordMatrix - col - 1;
        }
        uint16_t returnValue = col + (row * newColsWordMatrix);

        if (returnValue > numPixelsWordMatrix) {
            Serial.println(
                "[ERROR] getFrontMatrixIndex() returnValue out of Bounds");
        }

        return numPixelsWordMatrix + 4 - 1 - returnValue;
    };

    //------------------------------------------------------------------------------

    virtual const void getMinuteArray(uint16_t *returnArr,
                                      uint8_t col) override {
        for (uint8_t i = 4; i > 0; i--) {
            returnArr[i] = i;
        }
    };
};

De10x11Fred_t _de10x11Fred;