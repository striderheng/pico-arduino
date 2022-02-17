//
// hV_Utilities.cpp
// Library C++ code
// ----------------------------------
//
// Project      highView Library Suite
//
// Created by   Rei Vilo, 01 Jun 2013
//
// Copyright    © Rei Vilo, 2010-2021
// Licence      Attribution-NonCommercial-ShareAlike 4.0 Unported (CC BY-NC-SA 4.0)
//
// See          hV_Utilities.h for references
//

// Library header
#include "hV_Utilities.h"
#include "stdarg.h"
#include "stdio.h"

void delay_ms(uint32_t ms)
{
    uint32_t chrono = millis() + ms;
    while (millis() < chrono);
}

char bufferIn[128];
char bufferOut[128];
char bufferFormat[32];

// Code
// Utilities
String formatString(const char * format, ...)
{
    memset(&bufferOut, 0x00, sizeof(bufferOut));
    va_list args;
    va_start(args, format);
    vsprintf(bufferOut, format, args);

    va_end(args);
    return String(bufferOut);
}

String trimString(String text)
{
    String work = "";
    bool flag = true;
    char c;

    uint8_t index;
    uint8_t start, end;

    // Upwards from start
    index = 0;
    flag = true;
    while ((index < text.length()) and flag)
    {
        if ((text.charAt(index) != '\n') and (text.charAt(index) != '\r') and (text.charAt(index) != ' ') and (text.charAt(index) != '\t'))
        {
            flag = false;
            start = index;
        }
        index++;
    }

    // Downwards from end
    index = text.length();
    flag = true;
    while ((index > 0) and flag)
    {
        if ((text.charAt(index) != '\n') and (text.charAt(index) != '\r') and (text.charAt(index) != ' ') and (text.charAt(index) != '\t'))
        {
            flag = false;
            end = index - 1;
        }
        index--;
    }

    return text.substring(start, end);
}

int32_t cos32x100(int32_t degreesX100)
{
    int32_t i = 1;

    if (degreesX100 < 0)
    {
        i = -i;
        degreesX100 = -degreesX100;
    }

    degreesX100 %= 36000;

    if (degreesX100 > 9000)
    {
        if (degreesX100 < 18000)
        {
            i = -i;
            degreesX100 = 18000 - degreesX100;
        }
        else if (degreesX100 < 27000)
        {
            i = -i;
            degreesX100 = degreesX100 - 18000;
        }
        else
        {
            degreesX100 = 36000 - degreesX100;
        }
    }

    if (degreesX100 < 1000)
    {
        return i * map(degreesX100,    0, 1000, 100, 98);
    }
    else if (degreesX100 < 2000)
    {
        return i * map(degreesX100, 1000, 2000,  98, 93);
    }
    else if (degreesX100 < 3000)
    {
        return i * map(degreesX100, 2000, 3000,  93, 86);
    }
    else if (degreesX100 < 4000)
    {
        return i * map(degreesX100, 3000, 4000,  86, 76);
    }
    else if (degreesX100 < 5000)
    {
        return i * map(degreesX100, 4000, 5000,  76, 64);
    }
    else if (degreesX100 < 6000)
    {
        return i * map(degreesX100, 5000, 6000,  64, 50);
    }
    else if (degreesX100 < 7000)
    {
        return i * map(degreesX100, 6000, 7000,  50, 34);
    }
    else if (degreesX100 < 8000)
    {
        return i * map(degreesX100, 7000, 8000,  34, 17);
    }
    else
    {
        return i * map(degreesX100, 8000, 9000,  17,  0);
    }
}

int32_t sin32x100(int32_t degreesX100)
{
    return cos32x100(degreesX100 + 27000);
}

void convertPolar2Rectangle(uint16_t centerX, uint16_t centerY, uint16_t angle, uint16_t radius, uint16_t &rectangularX, uint16_t &rectangularY)
{
    rectangularX = (uint16_t)(centerX + radius * sin32x100(angle * 100) / 100);
    rectangularY = (uint16_t)(centerY - radius * cos32x100(angle * 100) / 100);
}

void convertRectangle2Polar(uint16_t centerX, uint16_t centerY, uint16_t rectangularX, uint16_t rectangularY, uint16_t &angle, uint16_t &radius)
{
    float fX = (float)rectangularX - centerX;
    float fY = (float)rectangularY - centerY;
    float fZ = sqrt(fX * fX + fY * fY);
    fX /= fZ;
    fY /= fZ;

    if ((fY == 0) and (fX > 0))
    {
        angle = 90;
    }
    else if ((fY == 0) and (fX < 0))
    {
        angle = 270;
    }
    else
    {
        float fAngle = -atan(fX / fY);
        fAngle *= 360 / 2 / PI;

        if (fY > 0)
        {
            fAngle += 180;
        }
        if ((fX < 0) and (fY < 0))
        {
            fAngle += 360;
        }
        angle = (uint16_t)fAngle;
    }
}
String utf2iso(String s)
{
    uint8_t c;

    s.toCharArray(bufferIn, s.length() + 1);
    // strcpy(bufferIn, s.c_str());

    memset(&bufferOut, 0x00, sizeof(bufferOut));

    // Serial.print("> ");
    // Serial.print(s);
    // Serial.print(" : ");
    // for (uint8_t i=0; i<strlen(bufferIn)+1; i++) {
    //  Serial.print((uint8_t)bufferIn[i], HEX);
    //  Serial.print(".");
    // }
    // Serial.println();

    for (uint8_t i = 0; i < strlen(bufferIn); i++)
    {
        c = (uint8_t)bufferIn[i];

        if (c < 0x80)
        {
            bufferOut[strlen(bufferOut)] = c;
        }
        else if (c == 0xc3)
        {
            bufferOut[strlen(bufferOut)] = (bufferIn[++i] + 64);
        }
        else if (c == 0xc2)
        {
            bufferOut[strlen(bufferOut)] = bufferIn[++i];
        }
        else if (c == 0xe2)
        {
            if ((bufferIn[i + 1] == 0x82) && (bufferIn[i + 2] == 0xac))
            {
                bufferOut[strlen(bufferOut)] = 0x80;
                i += 2;
            }
        }
    }
    //    bufferOut[strlen(bufferOut)+1] = 0;

    //    Serial.print("> ");
    // Serial.print(s);
    // Serial.print(" : ");
    // for (uint8_t i=0; i<strlen(bufferOut)+1; i++) {
    //  Serial.print((uint8_t)bufferOut[i], HEX);
    //  Serial.print(".");
    // }
    // Serial.println();

    return bufferOut;
}

String i32toa(int32_t number, int32_t unit, uint8_t decimal, uint8_t size)
{
    // Added unit, rounding, size and overflow #
    // ftoa(3431453, 1000, 2, 10) -> 343.1453 -> "    343.15"
    // ftoa(3431453, 1000, 4,  7) -> 343.1453 -> "#      "

    memset(&bufferIn, 0x00, sizeof(bufferIn));
    memset(&bufferOut, 0x00, sizeof(bufferOut));

    int32_t multiplier = 1;
    for (uint8_t i = 0; i < decimal; i++)
    {
        multiplier *= 10;
    }
    number = (number * multiplier * 10 / unit + 5) / 10 ;

    if (decimal > 0)
    {
        if (size > decimal)
        {
            sprintf(bufferFormat, "%%%dd.", size - decimal - 1);
        }
        else
        {
            strcpy(bufferFormat, "%0d.");
        }
        sprintf(bufferOut, bufferFormat, number / multiplier);

        if (number < 0)
        {
            number  = -number;
        }
        sprintf(bufferFormat, "%%0%dd", decimal);
        sprintf(bufferOut + strlen(bufferOut), bufferFormat, number % multiplier);
    }
    else
    {
        sprintf(bufferFormat, "%%%dd", size);
        sprintf(bufferOut, bufferFormat, number / multiplier);
    }

    if ((size > 0) && (strlen(bufferOut) > size))
    {
        strcpy(bufferOut, "#i");
    }
    return bufferOut;
}

String htoa(uint32_t number, uint8_t size)
{
    sprintf(bufferFormat, "%%0%dx", size);
    sprintf(bufferOut, bufferFormat, number);

    if ((size > 0) && (strlen(bufferOut) > size))
    {
        strcpy(bufferOut, "#h");
    }

    return bufferOut;
}

String ttoa(uint32_t number, uint8_t size)
{
    String s = "";
    memset(&bufferOut, 0x00, sizeof(bufferOut));
    // Automatic selection of the time unit: ms, s, mn, h

    if (number < (uint32_t)1000) // ms
    {
        sprintf(bufferFormat, "%%%ddms", (size > 2) ? size - 2 : 0);
        sprintf(bufferOut, bufferFormat, number);
    }
    else if (number < (uint32_t)60000) // s = ms/1000
    {
        number /= 100;
        sprintf(bufferFormat, "%%%dd", (size > 3) ? size - 3 : 0);
        sprintf(bufferOut, bufferFormat, number / 10);
        sprintf(bufferOut + strlen(bufferOut), ".%us", number % 10);
    }
    else if (number < (uint32_t)3600000) // mn = ms/1000/60
    {
        number /= (uint32_t)6000;
        sprintf(bufferFormat, "%%%dd", (size > 4) ? size - 4 : 0);
        sprintf(bufferOut, bufferFormat, number / 10);
        sprintf(bufferOut + strlen(bufferOut), ".%umn", number % 10);
    }
    else // h = ms/1000/60/60
    {
        number /= (uint32_t)360000;
        sprintf(bufferFormat, "%%%dd", (size > 3) ? size - 3 : 0);
        sprintf(bufferOut, bufferFormat, number / 10);
        sprintf(bufferOut + strlen(bufferOut), ".%uh", number % 10);
    }

    return bufferOut;
}

String btoa(uint32_t number, uint8_t size)
{
    if (size < 8)
    {
        return "#";
    }

    memset(&bufferOut, 0x00, sizeof(bufferOut));
    memset(&bufferOut, '0', size);
    uint8_t i = size;

    while ((number > 0) && (i > 0))
    {
        bufferOut[--i] = '0' + (number % 2);
        number >>= 1;
    }
    // if (i==0) strcpy(bufferOut, "#");

    return bufferOut;
}

uint16_t checkRange(uint16_t value, uint16_t valueMin, uint16_t valueMax)
{
    uint16_t localMin = min(valueMin, valueMax);
    uint16_t localMax = max(valueMin, valueMax);

    return min(max(localMin, value), localMax);
}

void setMinMax(uint16_t value, uint16_t &valueMin, uint16_t &valueMax)
{
    if (value < valueMin)
    {
        valueMin = value;
    }
    if (value > valueMax)
    {
        valueMax = value;
    }
}

uint32_t roundUp(uint32_t value, uint16_t modulo)
{
    uint32_t result = value / modulo;
    if ((value % modulo) > 0)
    {
        result++;
    }
    return result;
}

// Utilities
void swap(uint16_t &a, uint16_t &b)
{
    uint16_t w = a;
    a = b;
    b = w;
}
void swap(int16_t &a, int16_t &b)
{
    int16_t w = a;
    a = b;
    b = w;
}
void swap(uint8_t &a, uint8_t &b)
{
    uint8_t w = a;
    a = b;
    b = w;
}

