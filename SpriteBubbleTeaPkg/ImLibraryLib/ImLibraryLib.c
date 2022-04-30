#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>

VOID 
LibFunction (VOID)
{
    Print(L"LibFunction() is called!\n");
};

EFI_STATUS
EFIAPI 
ImLibConstructor (VOID)
{
    Print(L"ImLibConstructor() is called!\n");
    return EFI_SUCCESS;
};

EFI_STATUS
EFIAPI 
ImLibDestructor (VOID)
{
    Print(L"ImLibDestructor() is called!\n");
    return EFI_SUCCESS;
};