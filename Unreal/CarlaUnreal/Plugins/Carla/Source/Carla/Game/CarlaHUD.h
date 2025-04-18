// Copyright (c) 2024 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

// Workaround to fix Windows conflict: Windows changes the name of some functions (DrawText, LoadLibrary...)
// with Unicode / ANSI versions for his own API (DrawTextW, DrawTextA, LoadLibraryW, LoadLibraryA...).
// But the changes are global for the compiler. Deep in headers, Windows has something like:
// #ifdef UNICODE
//   #define DrawText  DrawTextW
//   #define LoadLibrary LoadLibraryW
// #else
//   #define DrawText  DrawTextA
//   #define LoadLibrary LoadLibraryA
// #endif
// Then the linker tries to find the function DrawTextW on an external DLL and an unresolved external error happens because
// Unreal has no function DrawTextW, it has just DrawText.
// We can fix that by just undefining the function that conflicts with the name of the Windows API in Unicode.
#undef DrawText

#include "Carla.h"

#include <util/ue-header-guard-begin.h>
#include "Containers/Array.h"
#include "GameFramework/HUD.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include <util/ue-header-guard-end.h>

#include "CarlaHUD.generated.h"

struct HUDString
{
  FString Str { "" };
  FVector Location;
  FColor Color;
  double TimeToDie;
};

/// Class to draw on HUD
UCLASS()
class CARLA_API ACarlaHUD : public AHUD
{
  GENERATED_BODY()

public:

  ACarlaHUD(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
  {
    PrimaryActorTick.bCanEverTick = false;
  }

  virtual void DrawHUD() override;

  /** Draw 2D debug text graphs on UI for the wheels, suspension and other systems */
  void DrawDebug(float& YL, float& YPos);

  UChaosWheeledVehicleMovementComponent* DebugVehicle = nullptr;

  void AddDebugVehicleForTelemetry(UChaosWheeledVehicleMovementComponent* NewDebugVehiclePtr)
  {
      DebugVehicle = NewDebugVehiclePtr;
  }

  void AddHUDString(const FString Str, const FVector Location, const FColor Color, double LifeTime);

private:
  TArray<HUDString> StringList;
};
