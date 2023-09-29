#include <unistd.h>
#include <fcntl.h>
typedef unsigned char uc;
typedef unsigned int ui;

void elf(uc input[], int n ){
  int i;
  for ( i = 0; i < n; i++ ){
    if ( input[i] < 32 ){
      input[i] = '.';
    }
    if ( input[i] > 126 ){
      input[i] = '.';
    }
  }
}

int sizeU(uc str[]){
  int i, size = 0;
  for ( i = 0; str[i] != '\0'; i++){
    size++;
  }
  return size;
}

int size(char str[]){
  int i, size = 0;
  for ( i = 0; str[i] != '\0'; i++){
    size++;
  }
  return size;
}

int strEU(uc str1[], uc str2[]){
  int equals = 1;
  int size1 = sizeU(str1);
  int size2 = sizeU(str2);
  if ( size1 != size2 ) {
    equals = 0;
  } else {
    int i;
    for ( i = 0; i < size1; i++ ){
      if (str1[i] != str2[i] ) {
        equals = 0;
        break;
      }
    }        
  }
  return equals;
}

int strE(char str1[], char str2[]){
  int equals = 1;
  int size1 = size(str1);
  int size2 = size(str2);
  if ( size1 != size2 ) {
    equals = 0;
  } else {
    int i;
    for ( i = 0; i < size1; i++ ){
      if (str1[i] != str2[i] ) {
        equals = 0;
        break;
      }
    }        
  }
  return equals;
}

void igualaStr(uc str1[], uc str2[]){
  int size2 = sizeU(str2);
  int i;
  for ( i = 0; i < size2; i++ ){
    str1[i] = str2[i];
  }
  str1[i] = '\0';
}

void invertStr(uc str[]){
  ui i, size = sizeU(str);
  uc troca;
  for ( i = 0; i < size/2 ; i++){
    troca = str[i];
    str[i] = str[size-i-1];
    str[size-i-1] = troca;
  }
}

void concat(uc str1[], uc str2[]){
  ui i, itStr2=0, size1 = sizeU(str1), size2 = sizeU(str2);
  for ( i = size1; i < size2+size1; i++ ){
    str1[i] = str2[itStr2];
    itStr2++;
  }
}

void addZ(uc strBin[]){
  ui sizeBin = sizeU(strBin);
  ui bitsTotalFaltantes = 32 - sizeBin;
  uc strAux[40] = "00000000000000000000000000000000";
  strAux[bitsTotalFaltantes] = '\0';
  concat(strAux, strBin);
  igualaStr(strBin, strAux);
}

ui power(int num, int n ){
  int i;
  ui acc;
  if ( n == 0 ) acc = 1;
  else acc = num;
  for ( i = 1; i < n; i++ ){
    acc = acc * num;
  }
  return acc;
}

void decToHex(int dec, uc hexd[][33], int *linha, int *coluna){
  int resto, digito=0;
  uc alg;
  while (dec != 0 ){
    resto = dec%16; 
    switch (resto){
      case 10:
        alg = 'a';
      break;
      case 11:
        alg = 'b';
      break;
      case 12:
        alg = 'c';
      break;
      case 13:
        alg = 'd';
      break;
      case 14:
        alg = 'e';
      break;
      case 15:
        alg = 'f';
      break;
      default:
        alg = resto + '0';
    }
    hexd[*linha][*coluna] = alg;
    (*coluna)++;
    dec = dec / 16;
    digito++;
  }
  if ( digito == 2 ){
    uc aux = hexd[*linha][(*coluna)-1];
    hexd[*linha][(*coluna)-1] = hexd[*linha][*coluna-2];
    hexd[*linha][(*coluna)-2] = aux;
  } else if ( digito == 1 ){
    (*coluna)++;
    hexd[*linha][(*coluna)-1] = hexd[*linha][*coluna-2];
    hexd[*linha][(*coluna)-2] = '0';
  } else {
    (*coluna) += 2;
    hexd[*linha][(*coluna)-1] = '0';
    hexd[*linha][(*coluna)-2] = '0';
  }
}

void decToHex2(uc strHex[], ui num){
  ui resto, itHex=0;
  uc alg='a';
  while (num != 0 ){
    resto = num%16;
    switch (resto){
      case 10:
        alg = 'a';
        break;
      case 11:
        alg = 'b';
      break;
      case 12:
        alg = 'c';
      break;
      case 13:
        alg = 'd';
      break;
      case 14:
        alg = 'e';
      break;
      case 15:
        alg = 'f';
      break;
      default:
        alg = resto + '0';
    }
    strHex[itHex] = alg;
    itHex++;
    num = num/16;
  }
  invertStr(strHex);
}

void decToBin(uc strBin[], ui num){
  ui resto, itBin=0;
  while (num != 0 ){
    resto = num%2;
    strBin[itBin] = resto + '0';
    itBin++;
    num = num/2;
  }
  strBin[itBin] = '\0';
  invertStr(strBin);
}

void changEnd(uc hex[], int sizeHex){
  uc aux[9];
  igualaStr(aux, hex);
  int i;
  for ( i = 0; i < sizeHex; i++ ){
    if ( i%2 == 0 ) {
      hex[sizeHex-i-2] = aux[i];
    } else {
      hex[sizeHex-i] = aux[i];
    }
  }
}

ui hexToDec(uc str[]){
  ui num = 0; 
  int size = sizeU(str);
  int i, alg, n = size-1;
  for (i = 0; i < size; i++){
    switch (str[i]){
      case 'a':
        alg = 10;
      break;
      case 'b':
        alg = 11;
      break;
      case 'c':
        alg = 12;
      break;
      case 'd':
        alg = 13;
      break;
      case 'e':
        alg = 14;
      break;
      case 'f':
        alg = 15;
      break;
      default:
        alg = str[i] - '0';
    }
    num = num + ( alg * power(16, n));
    n--;
  }
  return num;  
}

ui binToDec(uc strBin[]){
  ui num = 0;
  int size = sizeU(strBin);
  int i, alg, n = size-1;
  for ( i = 0; i < size; i++){
    alg = strBin[i] - '0';
    num = num + ( alg * power(2, n));
    n--;
  }
  return num;
}

void makeHexd(uc input[], int n, uc hexd[][33]){
  int i, linha=0, coluna=0; 
  for ( i = 0; i < n; i++ ){
    decToHex(input[i], hexd, &linha, &coluna);
    if ( coluna == 32 ) {   
      linha++;
      coluna = 0;
    }
  }
}

void intToChar(ui num, uc str[]){
  ui resto, itStr=0, ehNeg=0;
  int x = num;
  if ( num == 0 ) {
    str[itStr] = '0'; 
    itStr++;
  }
  if ( x < 0 ) {
    ehNeg = 1;
    num = -1*num;
  }
  while (num != 0){
    resto = num % 10;
    str[itStr] = resto + '0';
    itStr++;
    num = num/10;
  }
  if ( ehNeg ){
    str[itStr] = '-';
    itStr++;
  }
  str[itStr] = '\0';
  invertStr(str);
}

void fSHTab(uc hexd[][33], uc sectionHeaderTableAddress[]){
  int i;
  for ( i = 0; i < 8; i++ ){
    sectionHeaderTableAddress[i] = hexd[2][i];
  }
}

void fEntriesNum(uc hexd[][33], uc sectionHeaderTableEntriesNumber[]) {
  int i;
  for ( i = 0; i < 4; i++ ) {
    sectionHeaderTableEntriesNumber[i] = hexd[3][i];
  }
}

void fShstrtabEntrie(uc hexd[][33], uc shstrtabHEntrie[]){
  int i;
  for ( i = 0; i < 4; i++ ) {
    shstrtabHEntrie[i] = hexd[3][i+4];
  }
}

void fShstrtabAddr(ui sHTabAddrInt, ui shstrtabHEntrie, uc hexd[][33], uc shstrtabAddr[]){
  ui sHTabL = (sHTabAddrInt + (40*shstrtabHEntrie) + (16) )/16;
  ui sHTabC = (sHTabAddrInt + (40*shstrtabHEntrie) + (16) )%16;
  int i;
  for ( i = 0; i < 8; i++ ){
    shstrtabAddr[i] = hexd[sHTabL][(sHTabC*2)+i];
  }
}

void fNameAddr(ui sHTabAddrInt, uc hexd[][33],uc nameAdrress[], ui i){
  ui sHL = (sHTabAddrInt + (40*i) )/16;
  ui sHC = (sHTabAddrInt + (40*i) )%16;
  int j;
  for ( j = 0; j < 8; j++ ){
    nameAdrress[j] = hexd[sHL][(sHC*2)+j];
  } 
}

void fSize(ui sHTabAddrInt, uc hexd[][33], uc size[], ui i){
  ui sHL = (sHTabAddrInt + (40*i) + (20) )/16;
  ui sHC = (sHTabAddrInt + (40*i) + (20) )%16;
  int j;
  for ( j = 0; j < 8; j++ ){
    size[j] = hexd[sHL][(sHC*2)+j];
  } 
  size[j]='\0';
  changEnd(size, 8);
}

void fVma(ui sHTabAddrInt, uc hexd[][33], uc vma[], ui i){
  ui sHL = (sHTabAddrInt + (40*i) + (12) )/16;
  ui sHC = (sHTabAddrInt + (40*i) + (12) )%16;
  int j;
  for ( j = 0; j < 8; j++ ){
    vma[j] = hexd[sHL][(sHC*2)+j];
  } 
  vma[j]='\0';
  changEnd(vma, 8);
}

void fNameSec(ui sHTabAddrInt, uc input[], uc hexd[][33], ui shstrtabAddrInt, uc name[], uc i){
  uc nameAdrress[9];
  fNameAddr(sHTabAddrInt, hexd, nameAdrress, i);
  changEnd(nameAdrress, 8);
  ui nameAdrressInt = hexToDec(nameAdrress);
  int j = 0;
  while ( input[shstrtabAddrInt+nameAdrressInt+j] != '.' || j == 0 ) {
    name[j] = input[shstrtabAddrInt+nameAdrressInt+j];
    j++;
  }
  name[j] = '\0';
}

void sections(ui sHTabAddrInt, ui sHTabEntNumInt, ui shstrtabAddrInt, uc input[], uc hexd[][33]){
  write(1, "Sections:\nIdx Name Size VMA\n", 28);

  ui i;
  uc iChar[1];
  uc name[100];
  uc size[9];
  uc vma[9];

  for ( i = 0; i < sHTabEntNumInt; i++ ){
    write(1, " ", 1);
    iChar[0] = i+'0';
    write(1, iChar, 1);
    write(1, "  ", 2);
    fNameSec(sHTabAddrInt, input, hexd, shstrtabAddrInt, name, i);
    if ( sizeU(name) != 1 ) write(1, name, sizeU(name));
    else write(1, "  ", 2);
    write(1, "  ", 2);

    fSize(sHTabAddrInt, hexd, size, i);
    write(1, size, 8);
    write(1, "  ", 2);
    fVma(sHTabAddrInt, hexd, vma, i);
    write(1, vma, 8);
    write(1, "\n", 1);
  }
  write(1, "\n", 1);
}

void fAddr(ui sHTabAddrInt, uc  hexd[][33], uc adrress[], ui i){
  ui sHL = (sHTabAddrInt + (40*i) + (16) )/16;
  ui sHC = (sHTabAddrInt + (40*i) + (16) )%16;
  int j;
  for ( j = 0; j < 8; j++ ){
    adrress[j] = hexd[sHL][(sHC*2)+j];
  } 
  adrress[j]='\0';
  changEnd(adrress, 8);
}

void fSymbolAddr(ui symAddrInt, uc hexd[][33], uc symbolAddr[], ui j){
  ui sHL = (symAddrInt + (16*j) + (4) )/16;
  ui sHC = (symAddrInt + (16*j) + (4) )%16;
  int i;
  for ( i = 0; i < 8; i++ ){
    symbolAddr[i] = hexd[sHL][(sHC*2)+i];
  } 
  symbolAddr[i]='\0';
  changEnd(symbolAddr, 8);
}

void fSymbolInfo(ui symAddrInt, uc hexd[][33], uc symbolInfo[], ui j){
  ui sHL = (symAddrInt + (16*j) + (12) )/16;
  ui sHC = (symAddrInt + (16*j) + (12) )%16;
  int i;
  for ( i = 0; i < 2; i++ ){
    symbolInfo[i] = hexd[sHL][(sHC*2)+i];
  } 
  symbolInfo[i]='\0';
  changEnd(symbolInfo, 2);
}

void fSymbolSecEnt(ui symAddrInt, uc hexd[][33], uc symbolSecEnt[], ui j){
  ui sHL = (symAddrInt + (16*j) + (14) )/16;
  ui sHC = (symAddrInt + (16*j) + (14) )%16;
  int i;
  for ( i = 0; i < 4; i++ ){
    symbolSecEnt[i] = hexd[sHL][(sHC*2)+i];
  } 
  symbolSecEnt[i]='\0';
  changEnd(symbolSecEnt, 4);
}

void fSymbolSec(ui sHTabAddrInt, ui shstrtabAddrInt, ui symAddrInt, uc hexd[][33], uc input[], uc symbolSec[], ui j){
  uc symbolSecEnt[5];
  fSymbolSecEnt(symAddrInt, hexd, symbolSecEnt, j);
  ui symbolSecEntInt = hexToDec(symbolSecEnt);
  fNameSec(sHTabAddrInt, input, hexd, shstrtabAddrInt, symbolSec, symbolSecEntInt);
}

void fSymbolSi(ui symAddrInt, uc hexd[][33], uc symbolSi[], ui j){
  ui sHL = (symAddrInt + (16*j) + (8) )/16;
  ui sHC = (symAddrInt + (16*j) + (8) )%16;
  int i;
  for ( i = 0; i < 8; i++ ){
    symbolSi[i] = hexd[sHL][(sHC*2)+i];
  } 
  symbolSi[i]='\0';
  changEnd(symbolSi, 8);
}

void fSymbolNamAddr(ui symAddrInt, uc hexd[][33], uc symbolNamAddr[], ui j){
  ui sHL = (symAddrInt + (16*j) )/16;
  ui sHC = (symAddrInt + (16*j) )%16;
  int i;
  for ( i = 0; i < 8; i++ ){
    symbolNamAddr[i] = hexd[sHL][(sHC*2)+i];
  } 
  symbolNamAddr[i]='\0';
  changEnd(symbolNamAddr, 8);
}

void fSymbolNam(ui symAddrInt, uc input[], uc hexd[][33], ui strtabAdrressInt, uc symbolNam[], ui i){
  uc symbolNamAddr[9];
  fSymbolNamAddr(symAddrInt, hexd, symbolNamAddr, i);
  ui symbolNamAddrInt = hexToDec(symbolNamAddr);
  int j = 0;
  while ( input[strtabAdrressInt+symbolNamAddrInt+j] != '.' || j == 0 ) {
    symbolNam[j] = input[strtabAdrressInt+symbolNamAddrInt+j];
    j++;
  }
  symbolNam[j] = '\0';
}

void symbols(ui sHTabAddrInt, ui sHTabEntNumInt, ui shstrtabAddrInt, uc input[], uc hexd[][33]){

  write(1, "SYMBOL TABLE:\n", 14);

  ui i;
  ui symtabEntNum = 0;
  ui strtabEntNum = 0;
  uc name[100];
  uc symtab[8] = ".symtab";
  uc strtab[8] = ".strtab";

  for ( i = 0; i < sHTabEntNumInt; i++ ){
    fNameSec(sHTabAddrInt, input, hexd, shstrtabAddrInt, name, i);
    if (strEU(name, symtab)) symtabEntNum = i;
    if (strEU(name, strtab)) strtabEntNum = i;
  }

  uc symtabAdrress[9];
  uc symtabSize[9];
  fAddr(sHTabAddrInt, hexd, symtabAdrress, symtabEntNum);
  fSize(sHTabAddrInt, hexd, symtabSize, symtabEntNum);
  ui symAddrInt = hexToDec(symtabAdrress);
  ui symtabSizeInt = hexToDec(symtabSize);
  uc strtabAdrress[9];
  fAddr(sHTabAddrInt, hexd, strtabAdrress, strtabEntNum);
  ui strtabAdrressInt = hexToDec(strtabAdrress);

  ui j;
  ui numberOfSymbols = symtabSizeInt/16;
  uc symbolAddr[9];
  uc symbolInfo[3];
  ui symbolInfoInt;
  uc symbolSec[100];
  uc symbolSi[9];
  uc symbolNam[100];

  for ( j = 1; j < numberOfSymbols; j ++){
    fSymbolAddr(symAddrInt, hexd, symbolAddr, j);
    write(1, symbolAddr, 8);
    write(1, " ", 1);

    fSymbolInfo(symAddrInt, hexd, symbolInfo, j);
    symbolInfoInt = hexToDec(symbolInfo);
    if ( symbolInfoInt > 4 ) write(1, "g", 1);
    else write(1, "l", 1);
    write(1, "    ", 4);

    fSymbolSec(sHTabAddrInt, shstrtabAddrInt, symAddrInt, hexd, input, symbolSec, j);
    if ( sizeU(symbolSec) != 1 ) write(1, symbolSec, sizeU(symbolSec));
    else write(1, "*ABS*", 5);
    write(1, "    ", 4);

    fSymbolSi(symAddrInt, hexd, symbolSi, j);
    write(1, symbolSi, 8);
    write(1, " ", 1);

    fSymbolNam(symAddrInt, input, hexd, strtabAdrressInt, symbolNam, j);
    write(1, symbolNam, sizeU(symbolNam));
    write(1, "\n", 1);

  }
}

void fInstruc(ui txtAddrInt, uc hexd[][33], uc instru[], ui i){
  ui sHL = (txtAddrInt + (4*i) )/16;
  ui sHC = (txtAddrInt + (4*i) )%16;
  int j;
  for ( j = 0; j < 8; j++ ){
    instru[j] = hexd[sHL][(sHC*2)+j];
  } 
  instru[j]='\0';
}

void tipoU(ui *instruImmDecInt, ui *instruRdInt, ui instru){
  (*instruImmDecInt) = instru >> 12; 
  (*instruRdInt) = (instru >> 7) & 0b11111;
}

void tipoI(ui *instruImmDecInt, ui *instruRdInt, ui *instruRs1Int, ui instru){
  (*instruImmDecInt) = (instru & 0b10000000000000000000000000000000) + ((instru >> 1) & 0b1000000000000000000000000000000) + ((instru >> 2) & 0b100000000000000000000000000000) + ((instru >> 3) & 0b10000000000000000000000000000) +
    ((instru >> 4) & 0b1000000000000000000000000000) + ((instru >> 5) & 0b100000000000000000000000000) + ((instru >> 6) & 0b10000000000000000000000000) + ((instru >> 7) & 0b1000000000000000000000000) + ((instru >> 8) & 0b100000000000000000000000) +
    ((instru >> 9) & 0b10000000000000000000000) + ((instru >> 10) & 0b1000000000000000000000) + ((instru >> 11) & 0b100000000000000000000) + ((instru >> 12) & 0b10000000000000000000) + ((instru >> 13) & 0b1000000000000000000) +
    ((instru >> 14) & 0b100000000000000000) + ((instru >> 15) & 0b10000000000000000) + ((instru >> 16) & 0b1000000000000000) + ((instru >> 17) & 0b100000000000000) + ((instru >> 18) & 0b10000000000000) + ((instru >> 19) & 0b1000000000000) + ((instru >> 20) & 0b111111111111);  
  (*instruRdInt) = (instru >> 7) & 0b11111;
  (*instruRs1Int) = (instru >> 15) & 0b11111;
}

void tipoB(ui *instruImmDecInt, ui *instruRs1Int, ui *instruRs2Int, ui instru){
  (*instruImmDecInt) = (instru & 0b10000000000000000000000000000000) + ((instru >> 1) & 0b1000000000000000000000000000000) + ((instru >> 2) & 0b100000000000000000000000000000) + ((instru >> 3) & 0b10000000000000000000000000000) +
    ((instru >> 4) & 0b1000000000000000000000000000) + ((instru >> 5) & 0b100000000000000000000000000) + ((instru >> 6) & 0b10000000000000000000000000) + ((instru >> 7) & 0b1000000000000000000000000) + ((instru >> 8) & 0b100000000000000000000000) +
    ((instru >> 9) & 0b10000000000000000000000) + ((instru >> 10) & 0b1000000000000000000000) + ((instru >> 11) & 0b100000000000000000000) + ((instru >> 12) & 0b10000000000000000000) + ((instru >> 13) & 0b1000000000000000000) +
    ((instru >> 14) & 0b100000000000000000) + ((instru >> 15) & 0b10000000000000000) + ((instru >> 16) & 0b1000000000000000) + ((instru >> 17) & 0b100000000000000) + ((instru >> 18) & 0b10000000000000) + ((instru >> 19) & 0b1000000000000) + ((instru << 4) & 0b100000000000) +
    ((instru >> 20 ) & 0b11111100000) + ((instru >> 7 ) & 0b11110);  
  (*instruRs1Int) = (instru >> 15) & 0b11111;
  (*instruRs2Int) = (instru >> 20) & 0b11111;
}

void tipoS(ui *instruImmDecInt, ui *instruRs1Int, ui *instruRs2Int, ui instru){
  (*instruImmDecInt) = (instru & 0b10000000000000000000000000000000) + ((instru >> 1) & 0b1000000000000000000000000000000) + ((instru >> 2) & 0b100000000000000000000000000000) + ((instru >> 3) & 0b10000000000000000000000000000) +
    ((instru >> 4) & 0b1000000000000000000000000000) + ((instru >> 5) & 0b100000000000000000000000000) + ((instru >> 6) & 0b10000000000000000000000000) + ((instru >> 7) & 0b1000000000000000000000000) + ((instru >> 8) & 0b100000000000000000000000) +
    ((instru >> 9) & 0b10000000000000000000000) + ((instru >> 10) & 0b1000000000000000000000) + ((instru >> 11) & 0b100000000000000000000) + ((instru >> 12) & 0b10000000000000000000) + ((instru >> 13) & 0b1000000000000000000) +
    ((instru >> 14) & 0b100000000000000000) + ((instru >> 15) & 0b10000000000000000) + ((instru >> 16) & 0b1000000000000000) + ((instru >> 17) & 0b100000000000000) + ((instru >> 18) & 0b10000000000000) + ((instru >> 19) & 0b1000000000000) + ((instru >> 20) & 0b111111100000) +
    ((instru >> 7) & 0b11111);  
  (*instruRs1Int) = (instru >> 15) & 0b11111;
  (*instruRs2Int) = (instru >> 20) & 0b11111;
}

void tipoR(ui *instruRdInt, ui *instruRs1Int, ui *instruRs2Int, ui instru){
  (*instruRdInt) = (instru >> 7) & 0b11111;
  (*instruRs1Int) = (instru >> 15) & 0b11111;
  (*instruRs2Int) = (instru >> 20) & 0b11111;
}

void instrus(ui sHTabAddrInt, ui sHTabEntNumInt, ui shstrtabAddrInt, uc input[], uc hexd[][33]){
  write(1, "\nDisassembly of section .text:\n", 31);

  int i;
  ui textEntrieNumber = 0;
  uc name[100];
  uc text[8] = ".text";

  for ( i = 0; i < sHTabEntNumInt; i++ ){
    fNameSec(sHTabAddrInt, input, hexd, shstrtabAddrInt, name, i);
    if (strEU(name, text)) textEntrieNumber = i;
  }

  uc textAdrress[9];
  uc textSize[9];
  uc textVma[9];
  fAddr(sHTabAddrInt, hexd, textAdrress, textEntrieNumber);
  fSize(sHTabAddrInt, hexd, textSize, textEntrieNumber);
  ui textAdrressInt = hexToDec(textAdrress);
  ui textSizeInt = hexToDec(textSize);
  fVma(sHTabAddrInt, hexd, textVma, textEntrieNumber);

  ui symtabEntNum = 0;
  ui strtabEntNum = 0;
  uc name2[100];
  uc symtab[8] = ".symtab";
  uc strtab[8] = ".strtab";

  for ( i = 0; i < sHTabEntNumInt; i++ ){
    fNameSec(sHTabAddrInt, input, hexd, shstrtabAddrInt, name2, i);
    if (strEU(name2, symtab)) symtabEntNum = i;
    if (strEU(name2, strtab)) strtabEntNum = i;
  }

  uc symtabAdrress[9];
  uc symtabSize[9];
  fAddr(sHTabAddrInt, hexd, symtabAdrress, symtabEntNum);
  fSize(sHTabAddrInt, hexd, symtabSize, symtabEntNum);
  ui symAddrInt = hexToDec(symtabAdrress);
  ui symtabSizeInt = hexToDec(symtabSize);

  uc strtabAdrress[9];
  fAddr(sHTabAddrInt, hexd, strtabAdrress, strtabEntNum);
  ui strtabAdrressInt = hexToDec(strtabAdrress);

  ui j;
  ui numberOfSymbolsInText=0;
  ui numberOfSymbols = symtabSizeInt/16;
  uc symbolAddr[100][9];
  ui symbolAddrListInt[100];
  uc symbolSec[100];
  uc symbolNam[100][100];

  for ( j = 1; j < numberOfSymbols; j ++){
    fSymbolSec(sHTabAddrInt, shstrtabAddrInt, symAddrInt, hexd, input, symbolSec, j);
    if (strEU(symbolSec, text)){
      fSymbolAddr(symAddrInt, hexd, symbolAddr[numberOfSymbolsInText], j);
      symbolAddrListInt[numberOfSymbolsInText] = hexToDec(symbolAddr[numberOfSymbolsInText]);
      fSymbolNam(symAddrInt, input, hexd, strtabAdrressInt, symbolNam[numberOfSymbolsInText], j);
      numberOfSymbolsInText++;
    }
  }

  ui j2;
  ui aux;
  uc start[8] = "_start";
  for ( j2 = 0; j2 < numberOfSymbolsInText; j2++ ){
    if ( strEU(symbolNam[j2], start) ) aux = j2;    
  }

  ui numberOfInstrus = textSizeInt/4;
  uc instruCod[9];
  uc instruCodBin[33];
  uc instruCodfrag[3];
  ui instruFunct3Int;
  ui instruFunct7Int;
  ui instruImm1100Int;
  uc instruImmDec[10];
  ui instruImmDecInt;
  uc instruZimmDec[5];
  ui instruRdInt;
  ui instruRs1Int;
  ui instruRs2Int;

  ui adrressInstruInt = symbolAddrListInt[aux];
  uc adrressInstru[9];
  decToHex2(adrressInstru, adrressInstruInt);

  uc registradores[32][5] = { "zero", "ra", "sp", "gp", "tp", "t0", "t1", "t2", "s0", "s1",
    "a0", "a1", "a2", "a3", "a4", "a5", "a7","a8", "s2", "s3", "s4", "s5", "s6", "s7", "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6" };
  uc op[11][8] = { "0110111", "0010111", "1101111", "1100111", "1100011", 
    "0000011", "0100011", "0010011", "0110011",  "0001111", "1110011" };
  uc funct3[8][4] = { "000", "100", "110", "101", "111", "010", "011", "001" };
  uc funct7[2][8] = { "0000000", "0100000"};
  uc imm1100[2][13] = { "000000000000", "000000000001"};

  ui j3;
  ui j4;
  for ( j3 = 0; j3 < numberOfInstrus; j3++ ){

    for ( j4 = 0; j4 < numberOfSymbolsInText; j4++ ){
      if ( symbolAddrListInt[j4] == adrressInstruInt ){
        write(1, "\n000", 4);
        write(1, adrressInstru, 5);
        write(1, " <", 2);
        write(1, symbolNam[j4], sizeU(symbolNam[j4]));
        write(1, ">:\n", 3);
        break;
      }
    }
    write(1, adrressInstru, 5);
    write(1, ": ", 2);
    
    fInstruc(textAdrressInt, hexd, instruCod, j3);
    instruCodfrag[0] = instruCod[0];
    instruCodfrag[1] = instruCod[1];
    write(1, instruCodfrag, 2);
    write(1, " ", 1);
    instruCodfrag[0] = instruCod[2];
    instruCodfrag[1] = instruCod[3];
    write(1, instruCodfrag, 2);
    write(1, " ", 1);
    instruCodfrag[0] = instruCod[4];
    instruCodfrag[1] = instruCod[5];
    write(1, instruCodfrag, 2);
    write(1, " ", 1);
    instruCodfrag[0] = instruCod[6];
    instruCodfrag[1] = instruCod[7];
    write(1, instruCodfrag, 2);
    write(1, " ", 1);

    changEnd(instruCod, 8);
    decToBin(instruCodBin, hexToDec(instruCod));
    addZ(instruCodBin);
    int instru = binToDec(instruCodBin) ;
    int opcode = instru & 0b1111111;
    instruFunct3Int = (instru >> 12) & 0b111;
    instruFunct7Int = (instru >> 25) & 0b1111111;
    
    if (  opcode == binToDec(op[0]) ){
      write(1, "lui ", 4);
      tipoU(&instruImmDecInt, &instruRdInt, instru);

      write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
      write(1, ", ", 2);
      intToChar(instruImmDecInt, instruImmDec);
      write(1, instruImmDec, sizeU(instruImmDec));

    } else if (opcode == binToDec(op[1])){
      write(1, "auipc ", 6);
      tipoU(&instruImmDecInt, &instruRdInt, instru);

      write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
      write(1, ", ", 2);
      intToChar(instruImmDecInt, instruImmDec);
      write(1, instruImmDec, sizeU(instruImmDec));

    } else if (opcode == binToDec(op[2])){
      write(1, "jal ", 4);

      instruImmDecInt = (instru & 0b10000000000000000000000000000000) + ((instru >> 1) & 0b1000000000000000000000000000000) + ((instru >> 2) & 0b100000000000000000000000000000) + ((instru >> 3) & 0b10000000000000000000000000000) +
      ((instru >> 4) & 0b1000000000000000000000000000) + ((instru >> 5) & 0b100000000000000000000000000) + ((instru >> 6) & 0b10000000000000000000000000) + ((instru >> 7) & 0b1000000000000000000000000) + ((instru >> 8) & 0b100000000000000000000000) +
      ((instru >> 9) & 0b10000000000000000000000) + ((instru >> 10) & 0b1000000000000000000000) + ((instru >> 11) & 0b100000000000000000000) + ((instru) & 0b11111111000000000000) + ((instru >> 9) & 0b100000000000) + ((instru >> 20) & 0b11111111110);  
      
      instruRdInt = (instru >> 7) & 0b11111;

      write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
      write(1, ", ", 2);

      uc adrress[6];
      ui adrressInt = adrressInstruInt;
      ui j5;
      adrressInt += instruImmDecInt;
      decToHex2(adrress, adrressInt);
      write(1, "0x", 2);
      write(1, adrress, sizeU(adrress));
      write(1, " <", 2);
      for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
        if( adrressInt == symbolAddrListInt[j5] ){
          write(1, symbolNam[j5], sizeU(symbolNam[j5]));
          break;
        }
      }
      write(1,">", 1);

    } else if (opcode == binToDec(op[3])){
      write(1, "jalr ", 5);
      tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

      write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
      write(1, ", ", 2);
      intToChar(instruImmDecInt, instruImmDec);
      write(1, instruImmDec, sizeU(instruImmDec));
      write(1, "(", 1);
      write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
      write(1, ")", 1);

    } else if (opcode == binToDec(op[4])){
      if ( instruFunct3Int == binToDec(funct3[0]) ){
        write(1, "beq ", 4);
        tipoB(&instruImmDecInt, &instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);

        uc adrress[6];
        ui adrressInt = adrressInstruInt;
        ui j5;
        adrressInt += instruImmDecInt;
        decToHex2(adrress, adrressInt);
        write(1, "0x", 2);
        write(1, adrress, sizeU(adrress));
        write(1, " <", 2);
        for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
          if( adrressInt == symbolAddrListInt[j5] ){
            write(1, symbolNam[j5], sizeU(symbolNam[j5]));
            break;
          }
        }
        write(1,">", 1);

      } else if (instruFunct3Int == binToDec(funct3[7])){
        write(1, "bne ", 4);
        tipoB(&instruImmDecInt, &instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);

        uc adrress[6];
        ui adrressInt = adrressInstruInt;
        ui j5;
        adrressInt += instruImmDecInt;
        decToHex2(adrress, adrressInt);
        write(1, "0x", 2);
        write(1, adrress, sizeU(adrress));
        write(1, " <", 2);
        for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
          if( adrressInt == symbolAddrListInt[j5] ){
            write(1, symbolNam[j5], sizeU(symbolNam[j5]));
            break;
          }
        }
        write(1,">", 1);

      } else if (instruFunct3Int == binToDec(funct3[1])){
        write(1, "blt ", 4);
        tipoB(&instruImmDecInt, &instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);

        uc adrress[6];
        ui adrressInt = adrressInstruInt;
        ui j5;
        adrressInt += instruImmDecInt;
        decToHex2(adrress, adrressInt);
        write(1, "0x", 2);
        write(1, adrress, sizeU(adrress));
        write(1, " <", 2);
        for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
          if( adrressInt == symbolAddrListInt[j5] ){
            write(1, symbolNam[j5], sizeU(symbolNam[j5]));
            break;
          }
        }
        write(1,">", 1);

      } else if (instruFunct3Int == binToDec(funct3[3])){
        write(1, "bge ", 4);
        tipoB(&instruImmDecInt, &instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);

        uc adrress[6];
        ui adrressInt = adrressInstruInt;
        ui j5;
        adrressInt += instruImmDecInt;
        decToHex2(adrress, adrressInt);
        write(1, "0x", 2);
        write(1, adrress, sizeU(adrress));
        write(1, " <", 2);
        for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
          if( adrressInt == symbolAddrListInt[j5] ){
            write(1, symbolNam[j5], sizeU(symbolNam[j5]));
            break;
          }
        }
        write(1,">", 1);

      } else if (instruFunct3Int == binToDec(funct3[2])){
        write(1, "bltu ", 5);
        tipoB(&instruImmDecInt, &instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);

        uc adrress[6];
        ui adrressInt = adrressInstruInt;
        ui j5;
        adrressInt += instruImmDecInt;
        decToHex2(adrress, adrressInt);
        write(1, "0x", 2);
        write(1, adrress, sizeU(adrress));
        write(1, " <", 2);
        for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
          if( adrressInt == symbolAddrListInt[j5] ){
            write(1, symbolNam[j5], sizeU(symbolNam[j5]));
            break;
          }
        }
        write(1,">", 1);

      } else if (instruFunct3Int == binToDec(funct3[4])){
        write(1, "bgeu ", 5);
        tipoB(&instruImmDecInt, &instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);

        uc adrress[6];
        ui adrressInt = adrressInstruInt;
        ui j5;
        adrressInt += instruImmDecInt;
        decToHex2(adrress, adrressInt);
        write(1, "0x", 2);
        write(1, adrress, sizeU(adrress));
        write(1, " <", 2);
        for ( j5 = 0; j5 < numberOfSymbolsInText; j5++ ){
          if( adrressInt == symbolAddrListInt[j5] ){
            write(1, symbolNam[j5], sizeU(symbolNam[j5]));
            break;
          }
        }
        write(1,">", 1);

      }
    } else if (opcode == binToDec(op[5])){

      if ( instruFunct3Int == binToDec(funct3[0])){
        write(1, "lb ", 3);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      } else if (instruFunct3Int == binToDec(funct3[7])){
        write(1, "lh ", 3);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      } else if (instruFunct3Int == binToDec(funct3[5])){
        write(1, "lw ", 3);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      } else if (instruFunct3Int == binToDec(funct3[1])){
        write(1, "lbu ", 4);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      } else if (instruFunct3Int == binToDec(funct3[3])){
        write(1, "lhu ", 4);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      }
    } else if (opcode == binToDec(op[6])){    
      if ( instruFunct3Int == binToDec(funct3[0])){
        write(1, "sb ", 3);
        tipoS(&instruImmDecInt,&instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      } else if (instruFunct3Int == binToDec(funct3[7])){
        write(1, "sh ", 3);
        tipoS(&instruImmDecInt,&instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      } else if (instruFunct3Int == binToDec(funct3[5])){
        write(1, "sw ", 3);
        tipoS(&instruImmDecInt,&instruRs1Int, &instruRs2Int, instru);

        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, "(", 1);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ")", 1);

      }

    } else if (opcode == binToDec(op[7])){
      if ( instruFunct3Int == binToDec(funct3[0])){
        write(1, "addi ", 5);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
      
      } else if (instruFunct3Int == binToDec(funct3[5])){
        write(1, "slti ", 5);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
      
      } else if (instruFunct3Int == binToDec(funct3[6])){
        write(1, "sltiu ", 6);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
      
      } else if (instruFunct3Int == binToDec(funct3[1])){
        write(1, "xori ", 5);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));

      } else if (instruFunct3Int == binToDec(funct3[2])){
        write(1, "ori ", 4);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
      
      } else if (instruFunct3Int == binToDec(funct3[4])){
        write(1, "andi ", 5);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
      
      } else if (instruFunct3Int == binToDec(funct3[7])){
        write(1, "slli ", 5);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));

      } else if (instruFunct3Int == binToDec(funct3[3])){
        if (instruFunct7Int == binToDec(funct7[0])){
          write(1, "srli ", 5);
          tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          intToChar(instruImmDecInt, instruImmDec);
          write(1, instruImmDec, sizeU(instruImmDec));

        } else if ( instruFunct7Int == binToDec(funct7[1])){
          write(1, "srai ", 5);
          tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);

          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          intToChar(instruImmDecInt, instruImmDec);
          write(1, instruImmDec, sizeU(instruImmDec));

        }
      }
    } else if (opcode == binToDec(op[8])){
      if ( instruFunct3Int == binToDec(funct3[0])){
        if (instruFunct7Int == binToDec(funct7[0])){
          write(1, "add ", 4);
          tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
          
          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

        } else if (instruFunct7Int == binToDec(funct7[1])){
          write(1, "sub ", 4);
          tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
          
          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

        }
      } else if (instruFunct3Int == binToDec(funct3[7])){
        write(1, "sll ", 4);
        tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

      } else if (instruFunct3Int == binToDec(funct3[5])){
        write(1, "slt ", 4);
        tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

      } else if (instruFunct3Int == binToDec(funct3[6])){
        write(1, "sltu ", 5);
        tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

      } else if (instruFunct3Int == binToDec(funct3[1])){
        write(1, "xor ", 4);
        tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
        write(1, ", ", 2);
        write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

      } else if (instruFunct3Int == binToDec(funct3[3])){
        if (instruFunct7Int == binToDec(funct7[0])){
          write(1, "srl ", 4);
          tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

        } else if (instruFunct7Int == binToDec(funct7[1])) {
          write(1, "sra ", 3);
          tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

        }
      } else if (instruFunct3Int == binToDec(funct3[2])){
        write(1, "or ", 3);
          tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

      } else if (instruFunct3Int == binToDec(funct3[4])){
        write(1, "and ", 4);
          tipoR(&instruRdInt, &instruRs1Int, &instruRs2Int, instru);
        
          write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
          write(1, ", ", 2);
          write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));
          write(1, ", ", 2);
          write(1, registradores[instruRs2Int], sizeU(registradores[instruRs2Int]));

      }
    } else if (opcode == binToDec(op[9])){
      if ( instruFunct3Int == binToDec(funct3[0])){
        write(1, "fence ", 6);
        ui pred = (instru >> 24) & 0b1111;
        ui suc = (instru >> 20 ) & 0b1111;
        int aux1=0;
        if ( ((pred >> 3) & 0b1) == 0b1) {
          write(1, "i", 1);
          aux1=1;
        }
        if ( ((pred >> 2) & 0b1) == 0b1 ) {
          write(1, "o", 1);
          aux1=1;
        }
        if ( ((pred >> 1) & 0b1) == 0b1 ) {
          write(1, "r", 1);
          aux1=1;
        }
        if ( (pred & 0b1) == 0b1 ) {
          write(1, "w", 1);
          aux1=1;
        }
        if ( aux1 ) write(1, ", ", 2);

        if ( ((suc >> 3) & 0b1) == 0b1) {
          write(1, "i", 1);
          aux1=1;
        }
        if ( ((suc >> 2) & 0b1) == 0b1 ) {
          write(1, "o", 1);
          aux1=1;
        }
        if ( ((suc >> 1) & 0b1) == 0b1 ) {
          write(1, "r", 1);
          aux1=1;
        }
        if ( (suc & 0b1) == 0b1 ) {
          write(1, "w", 1);
          aux1=1;
        }

      } else if ( instruFunct3Int == binToDec(funct3[7])){
        write(1, "fence.i", 7);
      }
    } else if (opcode == binToDec(op[10])){
      instruImm1100Int = (instru >> 20) & 0b111111111111;
      if ( instruFunct3Int == binToDec(funct3[0])){
        if (instruImm1100Int == binToDec(imm1100[0])){
          write(1, "ecall", 5);
        } else if (instruImm1100Int == binToDec(imm1100[1])){
          write(1, "ebreak", 6);
        }
      } else if (instruFunct3Int == binToDec(funct3[7])){
        write(1, "csrrw ", 6);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));

      } else if (instruFunct3Int == binToDec(funct3[5])){
        write(1, "csrrs ", 6);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));

      } else if (instruFunct3Int == binToDec(funct3[6])){
        write(1, "csrrc ", 6);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, ", ", 2);
        write(1, registradores[instruRs1Int], sizeU(registradores[instruRs1Int]));

      } else if (instruFunct3Int == binToDec(funct3[3])){
        write(1, "csrrwi ", 7);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, ", ", 2);
        intToChar(instruRs1Int, instruZimmDec);
        write(1, instruZimmDec, sizeU(instruZimmDec));

      } else if (instruFunct3Int == binToDec(funct3[2])){
        write(1, "csrrsi ", 7);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, ", ", 2);
        intToChar(instruRs1Int, instruZimmDec);
        write(1, instruZimmDec, sizeU(instruZimmDec));
      
      } else if (instruFunct3Int == binToDec(funct3[4])){
        write(1, "csrrci ", 7);
        tipoI(&instruImmDecInt, &instruRdInt, &instruRs1Int, instru);
        
        write(1, registradores[instruRdInt], sizeU(registradores[instruRdInt]));
        write(1, ", ", 2);
        intToChar(instruImmDecInt, instruImmDec);
        write(1, instruImmDec, sizeU(instruImmDec));
        write(1, ", ", 2);
        intToChar(instruRs1Int, instruZimmDec);
        write(1, instruZimmDec, sizeU(instruZimmDec));
      } 
    } else {
      write(1, "<unknown>", 9);
    }
    adrressInstruInt += 4;
    decToHex2(adrressInstru, adrressInstruInt);
    write(1, "\n", 1);
  }

}

int main (int argc, char *argv[]){

  uc input[100000];
  int fileDescriptor = open(argv[2], O_RDONLY);
  int n = read(fileDescriptor, input, 100000);

  write(1, "\n", 1);
  write(1, argv[2], size(argv[2]));
  write(1, ": file format elf32-littleriscv\n\n", 33);

  uc hexd[100][33];
  makeHexd(input, n, hexd);
  elf(input, n);

  uc sectionHeaderTableAddress[9] ;
  fSHTab(hexd, sectionHeaderTableAddress);
  changEnd(sectionHeaderTableAddress, 8);
  ui  sHTabAddrInt = hexToDec(sectionHeaderTableAddress);

  uc sectionHeaderTableEntriesNumber[5];
  fEntriesNum(hexd, sectionHeaderTableEntriesNumber);
  changEnd(sectionHeaderTableEntriesNumber, 4);
  ui sHTabEntNumInt = hexToDec(sectionHeaderTableEntriesNumber);

  uc shstrtabHEntrie[5];
  fShstrtabEntrie(hexd, shstrtabHEntrie);
  changEnd(shstrtabHEntrie, 4);
  ui shstrtabHEntrieInt = hexToDec(shstrtabHEntrie);

  uc shstrtabAddr[9];
  fShstrtabAddr(sHTabAddrInt, shstrtabHEntrieInt , hexd, shstrtabAddr);
  changEnd(shstrtabAddr, 8);
  ui shstrtabAddrInt = hexToDec(shstrtabAddr);
   
  char flagd[3] = "-d";
  char flagt[3] = "-t";
  char flagh[3] = "-h";
  
  if (strE(argv[1], flagd)){
    instrus(sHTabAddrInt, sHTabEntNumInt, shstrtabAddrInt, input,  hexd);
  } else if (strE(argv[1], flagt)){
    symbols(sHTabAddrInt, sHTabEntNumInt, shstrtabAddrInt, input,  hexd);
  } else if (strE(argv[1], flagh)){
    sections(sHTabAddrInt, sHTabEntNumInt, shstrtabAddrInt, input,  hexd);
  }

  close(fileDescriptor);
  return 0;
}