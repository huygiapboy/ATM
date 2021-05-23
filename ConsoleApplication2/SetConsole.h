#pragma once
#include<Windows.h>	
#include<iostream>
using namespace std;
void SetWindowSize(SHORT width, SHORT height); // Thay doi kich thuoc Console
void DisableResizeWindow();  // Chong chinh kich co Console
void SetScreenBufferSize(SHORT width, SHORT height); // Thay doi vi tri man hinh nhin thay
void ShowScrollbar(BOOL Show);  // An hien thanh cuon
void SetColor(int backgound_color, int text_color); // Thay doi mau chu va nen
void GoTo(SHORT posX, SHORT posY);  // Di toi toa do
void ShowCur(bool CursorVisibility); // An/ hien con tro
void DisableSelection(); // xoa boi den txt
void setFontSize(int FontSize);  // Thay doi co chu
void delete_(SHORT posX, SHORT posY, size_t n);
void DisableCtrButton(bool Close, bool Min, bool Max); //Vo hieu hoa cac nut bam
void SETCONSOLE(); //Cai dat man hinh