#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>//Ihaventeatenyet_002 ++
#include "ImLibraryLib/ImLibraryLib.h"//Ihaventeatenyet_004 ++


#define Get_Graphics_Resolution 0//Ihaventeatenyet_002 ++
#define Get_Current_Time 0//Ihaventeatenyet_003 ++
#define Create_Library_Test 1//Ihaventeatenyet_004 ++

//Ihaventeatenyet_003 ++>>
#if Get_Current_Time
EFI_STATUS
GetCurrentTime ( VOID )
{
    EFI_STATUS           Status = EFI_SUCCESS;
    EFI_TIME             time;
    UINTN                i=0;

    for(i=0;i<10;i++){
    gST->RuntimeServices->GetTime (&time,NULL);
    Print(L"CurrentTime:%d-%d-%d %d:%d:%d\n",
                              time.Year,
                              time.Month,
                              time.Day,
                              time.Hour,
                              time.Minute,
                              time.Second);
    gST->BootServices->Stall(2*1000000);//Delay 2s
    }
    return Status;
}
#endif
//Ihaventeatenyet_003 ++<<

//Ihaventeatenyet_002 ++>>
#if Get_Graphics_Resolution
EFI_STATUS
GetGraphicsResolution ( VOID )
{
    EFI_STATUS           Status = EFI_SUCCESS;
    UINTN                HandleCount=0;
    EFI_HANDLE           *Handles;
    EFI_HANDLE           *ImageHandle;
    EFI_GRAPHICS_OUTPUT_PROTOCOL *GOP;
    UINTN                i = 0;
    UINTN                SizeOfInfo;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;

    Status = gBS->LocateHandleBuffer (
                               ByProtocol,
                               &gEfiGraphicsOutputProtocolGuid,
                               NULL,
                               &HandleCount,
                               &Handles
                               );
    //Print(L"       LocateHandleBuffer Status = %r\n",Status);
    //Print(L"       HandleCount = %d\n",HandleCount);
    if(EFI_ERROR(Status)){
        Print(L"       Fail to LocateHandleBuffer\n");
        return Status;
    }

    Status = gBS->OpenProtocol (
                         Handles[0],
                         &gEfiGraphicsOutputProtocolGuid,
                         (VOID **)&GOP,
                         ImageHandle,
                         NULL,
                         EFI_OPEN_PROTOCOL_GET_PROTOCOL
    );
    if(EFI_ERROR(Status)){
    Print(L"       Fail to OpenProtocol\n");
    return Status;
    }

    for(i=0;i< GOP->Mode->MaxMode;i++){
    Status = GOP->QueryMode (
      GOP,
      i,
      &SizeOfInfo,
      &Info
    );

    Print(L"       Mode= %x ,VerticalResolution= %x ,HorizontalResolution= %x\n",i,
                                                          Info->VerticalResolution,
                                                          Info->HorizontalResolution,
                                                          SizeOfInfo);
    }

    return Status;
}
#endif
//Ihaventeatenyet_002 ++<<

EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
  {
      //Print(L"       Hello BubbleTea\n");
//Ihaventeatenyet_002 ++>>
#if Get_Graphics_Resolution
    GetGraphicsResolution();
#endif
//Ihaventeatenyet_002 ++<<
//Ihaventeatenyet_003 ++>>
#if Get_Current_Time
    GetCurrentTime();
#endif
//Ihaventeatenyet_003 ++<<
//Ihaventeatenyet_004 ++>>
#if Create_Library_Test
    LibFunction();
#endif
//Ihaventeatenyet_004 ++<<
      return 0;
  }