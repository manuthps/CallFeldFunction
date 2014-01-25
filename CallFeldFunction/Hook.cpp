#include "Hook.h"


Hooker::Hooker(void)
{
}


Hooker::~Hooker(void)
{
}


//Zum Hooken von Funktionen
bool Hooker::DetourFunc(BYTE* oldFunc, BYTE* newFunc, DWORD len)
{
    BYTE* newMem4base = NULL;
    DWORD dwOld;

    newMem4base = ( BYTE* )malloc( 5+len );

    if( newMem4base == NULL )
        return false;

    for( DWORD i = 0; i < ( len+5 ); i++ )
        newMem4base[i] = 0x90;

    VirtualProtect( oldFunc, len, PAGE_READWRITE, &dwOld );

    memcpy( newMem4base, oldFunc, len );
    oldFunc[0] = 0xE8;
    *( DWORD* )( oldFunc+0x01 ) = DWORD( newFunc-oldFunc-5 );
    oldFunc[5] = 0xE9;
    *( DWORD* )( oldFunc+0x06 ) = DWORD( newMem4base-( oldFunc+0x5 )-5 );
    newMem4base += len;
    newMem4base[0] = 0xE9;
    *( DWORD* )( newMem4base+0x01 ) = DWORD( ( oldFunc+10 )-newMem4base-5 );

    for( DWORD i = 10; i <len; i++ )
        oldFunc[i] = 0x90;

    return true;
}