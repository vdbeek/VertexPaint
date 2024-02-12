#include "VertexPaintFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "PhysicsEngine/PhysicsSettings.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Materials/MaterialInstance.h"
#include "PhysicsEngine/BodySetup.h"
#include "Engine/GameInstance.h"

#include "Runtime/Engine/Classes/Engine/LatentActionManager.h"
#include "ColorsOfEachChannelLatentAction.h"
#include "ColorsOfEachChannelAsyncTask.h"

#include "Engine/StaticMesh.h"
#include "StaticMeshResources.h"
#include "Engine/SkeletalMesh.h"
#include "Components/SkeletalMeshComponent.h"
#include "Rendering/SkeletalMeshRenderData.h"
#include "Components/SplineMeshComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/BoxComponent.h"


#if ENGINE_MAJOR_VERSION == 5

#include "Components/DynamicMeshComponent.h"

#include "GeometryCollection/GeometryCollectionComponent.h"
#include "GeometryCollection/GeometryCollection.h"
#include "GeometryCollection/GeometryCollectionObject.h"

#include "ChaosWheeledVehicleMovementComponent.h"
#include "ChaosCloth/ChaosClothingSimulation.h"
#include "ChaosCloth/ChaosClothingSimulationInteractor.h"
#include "ClothingAsset.h"

#include "PhysicsEngine/PhysicsAsset.h"

#if ENGINE_MINOR_VERSION >= 2
#include "StaticMeshComponentLODInfo.h"
#include "Engine/Level.h"
#endif

#endif



//--------------------------------------------------------

// Print Task Log

void VertexPaintFunctions::PrintTaskLog(FVertexPaintDebugSettings debugSettings, const FString text, FColor screenTextColor) {

	if (debugSettings.worldTaskWasCreatedIn) {

		if (debugSettings.printLogsToScreen || debugSettings.printLogsToOutputLog)
			UKismetSystemLibrary::PrintString(debugSettings.worldTaskWasCreatedIn, text, debugSettings.printLogsToScreen, debugSettings.printLogsToOutputLog, screenTextColor, debugSettings.printLogsToScreen_Duration);
	}

	else {

		if (debugSettings.printLogsToOutputLog)
			UE_LOG(LogTemp, Log, TEXT("%s"), *text);
	}
}


//--------------------------------------------------------

// Get Closest Vertex Data On Mesh Wrapper

void VertexPaintFunctions::GetClosestVertexDataOnMesh_Wrapper(UVertexPaintDetectionComponent* VertexPaintComp, UPrimitiveComponent* meshComponent, FVertexDetectInfoStruct getClosestVertexDataStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {

	if (IsValid(VertexPaintComp)) {

		getClosestVertexDataStruct.meshComponent = meshComponent;

		// Note nothing more should be set here, because if a C++ Class calls the Paint/Detection Function Right Away it shouldn't lose out on anything being set

		VertexPaintComp->GetClosestVertexDataOnMesh(getClosestVertexDataStruct, additionalDataToPassThrough);
	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Get Closest Vertex Data on Mesh Failed because the Paint Component sent in isn't valid! Perhaps the Actor or Component is being destroyed. "));
	}
}


//--------------------------------------------------------

// Get All Vertex Colors Only Wrapper

void VertexPaintFunctions::GetAllVertexColorsOnly_Wrapper(UVertexPaintDetectionComponent* VertexPaintComp, UPrimitiveComponent* meshComponent, FVertexDetectGetColorsOnlyStruct getAllVertexColorsStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {

	if (IsValid(VertexPaintComp)) {

		getAllVertexColorsStruct.meshComponent = meshComponent;

		// Note nothing more should be set here, because if a C++ Class calls the Paint/Detection Function Right Away it shouldn't lose out on anything being set

		VertexPaintComp->GetAllVertexColorsOnly(getAllVertexColorsStruct, additionalDataToPassThrough);
	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Get All Vertex Colors Failed because the Paint Component sent in isn't valid! Perhaps the Actor or Component is being destroyed. "));
	}
}


//--------------------------------------------------------

// Paint on Mesh at Location Wrapper

void VertexPaintFunctions::PaintOnMeshAtLocation_Wrapper(UVertexPaintDetectionComponent* VertexPaintComp, UPrimitiveComponent* meshComponent, FVertexPaintAtLocationStruct paintAtLocationStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {

	if (IsValid(VertexPaintComp)) {

		paintAtLocationStruct.meshComponent = meshComponent;

		// Note nothing more should be set here, because if a C++ Class calls the Paint/Detection Function Right Away it shouldn't lose out on anything being set

		VertexPaintComp->PaintOnMeshAtLocation(paintAtLocationStruct, additionalDataToPassThrough);
	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Paint at Location Failed because the Paint Component sent in isn't valid! Perhaps the Actor or Component is being destroyed. "));
	}
}


//--------------------------------------------------------

// Paint Within Area Wrapper

void VertexPaintFunctions::PaintOnMeshWithinArea_Wrapper(UVertexPaintDetectionComponent* VertexPaintComp, UPrimitiveComponent* meshComponent, TArray<FVertexPainthWithinArea_ComponentToCheckIfIsWithinInfo> componentsToCheckIfIsWithin, FVertexPainthWithinAreaStruct paintWithinAreaStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {

	if (IsValid(VertexPaintComp)) {

		paintWithinAreaStruct.meshComponent = meshComponent;
		paintWithinAreaStruct.componentsToCheckIfIsWithin = componentsToCheckIfIsWithin;

		// Note nothing more should be set here, because if a C++ Class calls the Paint/Detection Function Right Away it shouldn't lose out on anything being set

		VertexPaintComp->PaintOnMeshWithinArea(paintWithinAreaStruct, additionalDataToPassThrough);
	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Paint on Mesh Within Area Failed because the Paint Component sent in isn't valid! Perhaps the Actor or Component is being destroyed. "));
	}
}


//--------------------------------------------------------

// Paint on Entire Mesh Wrapper

void VertexPaintFunctions::PaintOnEntireMesh_Wrapper(UVertexPaintDetectionComponent* VertexPaintComp, UPrimitiveComponent* meshComponent, FVertexPaintOnEntireMeshStruct paintOnEntireMeshStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {

	if (IsValid(VertexPaintComp)) {

		paintOnEntireMeshStruct.meshComponent = meshComponent;

		// Note nothing more should be set here, because if a C++ Class calls the Paint/Detection Function Right Away it shouldn't lose out on anything being set

		VertexPaintComp->PaintOnEntireMesh(paintOnEntireMeshStruct, additionalDataToPassThrough);
	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Paint on Entire Mesh Failed because the Paint Component sent in isn't valid! Perhaps the Actor or Component is being destroyed. "));
	}
}


//--------------------------------------------------------

// Paint Color Snippet On Mesh

void VertexPaintFunctions::PaintColorSnippetOnMesh_Wrappers(UVertexPaintDetectionComponent* VertexPaintComp, UPrimitiveComponent* meshComponent, FVertexPaintColorSnippetStruct paintColorSnippetStruct, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {

	if (IsValid(VertexPaintComp)) {

		paintColorSnippetStruct.meshComponent = meshComponent;

		// Note nothing more should be set here, because if a C++ Class calls the Paint/Detection Function Right Away it shouldn't lose out on anything being set

		VertexPaintComp->PaintColorSnippetOnMesh(paintColorSnippetStruct, additionalDataToPassThrough);
	}

	else {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Paint Color Snippet on Mesh Failed because the Vertex Paint Component sent in isn't valid! Perhaps the Actor or Component is being destroyed, or it hasn't been properly initialized. "));
	}
}


//--------------------------------------------------------

// Set Mesh Component Vertex Colors

void VertexPaintFunctions::SetMeshComponentVertexColors_Wrapper(UPrimitiveComponent* meshComponent, FVertexPaintSetMeshComponentVertexColors setMeshComponentVertexColorsSettings, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {


	if (IsValid(meshComponent)) {

		if (meshComponent->GetWorld()) {

			setMeshComponentVertexColorsSettings.taskWorld = meshComponent->GetWorld();
			setMeshComponentVertexColorsSettings.debugSettings.worldTaskWasCreatedIn = meshComponent->GetWorld();
		}

		setMeshComponentVertexColorsSettings.meshComponent = meshComponent;
		setMeshComponentVertexColorsSettings.actor = setMeshComponentVertexColorsSettings.meshComponent->GetOwner();

		VertexPaintFunctions::PrintTaskLog(setMeshComponentVertexColorsSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Set Mesh Component Vertex Colors on Actor: %s and Component: %s"), *setMeshComponentVertexColorsSettings.meshComponent->GetOwner()->GetName(), *setMeshComponentVertexColorsSettings.meshComponent->GetName()), FColor::Cyan);
	}


	FCalculateColorsInfo calculateColorsInfoTemp;
	calculateColorsInfoTemp.paintDetectionType = EVertexPaintDetectionType::SetMeshVertexColorsDirectly;
	calculateColorsInfoTemp.setMeshComponentVertexColorsSettings = setMeshComponentVertexColorsSettings;
	calculateColorsInfoTemp.initiatedByComponent = setMeshComponentVertexColorsSettings.optionalCallbackComponent;
	calculateColorsInfoTemp.additionalDataToPassThrough = additionalDataToPassThrough;
	calculateColorsInfoTemp.vertexPaintSettings = setMeshComponentVertexColorsSettings;
	calculateColorsInfoTemp.paintOnMeshColorSettings.applyVertexColorSettings.applyVertexColorSetting = EApplyVertexColorSetting::ESetVertexColor;


	calculateColorsInfoTemp.initialMeshVertexData.meshDataPerLOD.SetNum(1);
	calculateColorsInfoTemp.initialMeshVertexData.meshDataPerLOD[0].meshVertexColorsPerLODArray = setMeshComponentVertexColorsSettings.vertexColorsAtLOD0ToSet;

	FillCalculateColorsInfoFundementals(setMeshComponentVertexColorsSettings, calculateColorsInfoTemp);


	bool passedChecks_Local = true;

	if (!VertexPaintFunctions::CheckValidFundementals(setMeshComponentVertexColorsSettings, setMeshComponentVertexColorsSettings.meshComponent))
		passedChecks_Local = false;

	if (passedChecks_Local && !VertexPaintFunctions::CheckValidVertexPaintSettings(setMeshComponentVertexColorsSettings))
		passedChecks_Local = false;

	if (setMeshComponentVertexColorsSettings.meshComponent) {

		if (!IsValid(GetVertexPaintGameInstanceSubsystem(setMeshComponentVertexColorsSettings.meshComponent->GetWorld())))
			passedChecks_Local = false;
	}


	// If passed fundamental checks, then checks set mesh component vertex colors specific ones
	if (setMeshComponentVertexColorsSettings.vertexColorsAtLOD0ToSet.Num() <= 0) {


		VertexPaintFunctions::PrintTaskLog(setMeshComponentVertexColorsSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Set Mesh Component Vertex Colors but the color array passed in are 0 in length!")), FColor::Red);

		passedChecks_Local = false;
	}

	if (!passedChecks_Local) {

		VertexPaintFunctions::PrintTaskLog(setMeshComponentVertexColorsSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Check Valid Failed for Set Mesh Component Vertex Colors")), FColor::Red);

		VertexPaintFunctions::RunPaintSetMeshColorsCallbacks(calculateColorsInfoTemp);
		return;
	}


	if (VertexPaintFunctions::GetVertexPaintTaskQueue(setMeshComponentVertexColorsSettings.meshComponent->GetWorld()))
		VertexPaintFunctions::GetVertexPaintTaskQueue(setMeshComponentVertexColorsSettings.meshComponent->GetWorld())->AddCalculateColorsTaskToQueue(calculateColorsInfoTemp);
}


//--------------------------------------------------------

// Set Mesh Component Vertex Colors Using Serialized String

void VertexPaintFunctions::SetMeshComponentVertexColorsUsingSerializedString_Wrapper(UPrimitiveComponent* meshComponent, FVertexPaintSetMeshComponentVertexColorsUsingSerializedString setMeshComponentVertexColorsUsingSerializedStringSettings, FVertexDetectAdditionalDataToPassThrough additionalDataToPassThrough) {


	if (IsValid(meshComponent)) {

		if (meshComponent->GetWorld()) {

			setMeshComponentVertexColorsUsingSerializedStringSettings.taskWorld = meshComponent->GetWorld();
			setMeshComponentVertexColorsUsingSerializedStringSettings.debugSettings.worldTaskWasCreatedIn = meshComponent->GetWorld();
		}

		setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent = meshComponent;
		setMeshComponentVertexColorsUsingSerializedStringSettings.actor = setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent->GetOwner();

		VertexPaintFunctions::PrintTaskLog(setMeshComponentVertexColorsUsingSerializedStringSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Set Mesh Component Vertex Colors Using Serialized String on Actor: %s and Component: %s"), *setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent->GetOwner()->GetName(), *setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent->GetName()), FColor::Cyan);
	}


	FCalculateColorsInfo calculateColorsInfoTemp;
	calculateColorsInfoTemp.paintDetectionType = EVertexPaintDetectionType::SetMeshVertexColorsDirectlyUsingSerializedString;
	calculateColorsInfoTemp.setMeshComponentVertexColorsUsingSerializedStringSettings = setMeshComponentVertexColorsUsingSerializedStringSettings;
	calculateColorsInfoTemp.initiatedByComponent = setMeshComponentVertexColorsUsingSerializedStringSettings.optionalCallbackComponent;
	calculateColorsInfoTemp.additionalDataToPassThrough = additionalDataToPassThrough;
	calculateColorsInfoTemp.vertexPaintSettings = setMeshComponentVertexColorsUsingSerializedStringSettings;
	calculateColorsInfoTemp.paintOnMeshColorSettings.applyVertexColorSettings.applyVertexColorSetting = EApplyVertexColorSetting::ESetVertexColor;


	FillCalculateColorsInfoFundementals(setMeshComponentVertexColorsUsingSerializedStringSettings, calculateColorsInfoTemp);


	bool passedChecks_Local = true;

	if (!VertexPaintFunctions::CheckValidFundementals(setMeshComponentVertexColorsUsingSerializedStringSettings, setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent))
		passedChecks_Local = false;

	if (passedChecks_Local && !VertexPaintFunctions::CheckValidVertexPaintSettings(setMeshComponentVertexColorsUsingSerializedStringSettings))
		passedChecks_Local = false;

	if (setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent)
		if (!IsValid(GetVertexPaintGameInstanceSubsystem(setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent->GetWorld())))
			passedChecks_Local = false;


	if (setMeshComponentVertexColorsUsingSerializedStringSettings.serializedColorDataAtLOD0.Len() <= 0) {


		VertexPaintFunctions::PrintTaskLog(setMeshComponentVertexColorsUsingSerializedStringSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Set Mesh Component Vertex Colors Using Serialized String but the serializedColorData String passed in are 0 in length!")), FColor::Red);

		passedChecks_Local = false;
	}


	if (!passedChecks_Local) {


		VertexPaintFunctions::PrintTaskLog(setMeshComponentVertexColorsUsingSerializedStringSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Check Valid Failed for Set Mesh Component Vertex Colors Using Serialized String")), FColor::Red);

		VertexPaintFunctions::RunPaintSetMeshColorsCallbacks(calculateColorsInfoTemp);
		return;
	}

	if (VertexPaintFunctions::GetVertexPaintTaskQueue(setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent->GetWorld()))
		VertexPaintFunctions::GetVertexPaintTaskQueue(setMeshComponentVertexColorsUsingSerializedStringSettings.meshComponent->GetWorld())->AddCalculateColorsTaskToQueue(calculateColorsInfoTemp);
}


//--------------------------------------------------------

// Adjust Box Collision To Fill Area Between Two Locations

void VertexPaintFunctions::AdjustBoxCollisionToFillAreaBetweenTwoLocations(UBoxComponent* boxCollision, FVector fromLocation, FVector toLocation, float boxThickness) {

	if (!IsValid(boxCollision)) return;

	float distanceBetweenLocations = (fromLocation - toLocation).Size();

	if (distanceBetweenLocations > boxThickness) {

		FVector middlePointBetweenLocations = (fromLocation + toLocation) / 2;
		FRotator rotationFromLocationToLocation = UKismetMathLibrary::GetDirectionUnitVector(fromLocation, toLocation).ToOrientationRotator();

		boxCollision->SetBoxExtent(FVector(distanceBetweenLocations / 2, boxThickness, boxThickness), true);

		FHitResult hitResultTemp;
		boxCollision->SetWorldLocationAndRotation(middlePointBetweenLocations, rotationFromLocationToLocation, false, &hitResultTemp, ETeleportType::None);
	}
}


//--------------------------------------------------------

// Is World Valid

bool VertexPaintFunctions::IsWorldValid(UWorld* world) {

	if (!world) return false;
	if (!IsValid(world)) return false;
	if (!world->IsGameWorld()) return false;
	if (world->bIsTearingDown) return false;

	return true;
}


//-------------------------------------------------------

// Clamp Paint Strengths

FVertexDetectRGBAStruct VertexPaintFunctions::ClampPaintStrengths(FVertexDetectRGBAStruct applyVertexColorSettings) {


	// Clamps it so if the user sets like 0.000001, we will paint at the lowest amount of 1 when converted to FColor which range from 0-255
	if (applyVertexColorSettings.redColor > 0)
		applyVertexColorSettings.redColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.redColor, 0.005, 1);

	else if (applyVertexColorSettings.redColor < 0)
		applyVertexColorSettings.redColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.redColor, -1, -0.005);


	if (applyVertexColorSettings.greenColor > 0)
		applyVertexColorSettings.greenColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.greenColor, 0.005, 1);

	else if (applyVertexColorSettings.greenColor < 0)
		applyVertexColorSettings.greenColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.greenColor, -1, -0.005);


	if (applyVertexColorSettings.blueColor > 0)
		applyVertexColorSettings.blueColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.blueColor, 0.005, 1);

	else if (applyVertexColorSettings.blueColor < 0)
		applyVertexColorSettings.blueColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.blueColor, -1, -0.005);


	if (applyVertexColorSettings.alphaColor > 0)
		applyVertexColorSettings.alphaColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.alphaColor, 0.005, 1);

	else if (applyVertexColorSettings.alphaColor < 0)
		applyVertexColorSettings.alphaColor = UKismetMathLibrary::FClamp(applyVertexColorSettings.alphaColor, -1, -0.005);


	// For Apply Using Physics Surface as well
	if (applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply > 0)
		applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply = UKismetMathLibrary::FClamp(applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply, 0.005, 1);

	else if (applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply < 0)
		applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply = UKismetMathLibrary::FClamp(applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply, -1, -0.005);


	if (applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface > 0)
		applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface = UKismetMathLibrary::FClamp(applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface, 0.005, 1);

	else if (applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface < 0)
		applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface = UKismetMathLibrary::FClamp(applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface, -1, -0.005);


	return applyVertexColorSettings;
}


//-------------------------------------------------------

// Clamp Paint Limits

FVertexDetectRGBAStruct VertexPaintFunctions::ClampPaintLimits(FVertexDetectRGBAStruct applyColorSetting) {

	applyColorSetting.applyColorsUsingPhysicsSurface.physicsSurfacePaintLimit.paintLimitOnPhysicsSurface = UKismetMathLibrary::FClamp(applyColorSetting.applyColorsUsingPhysicsSurface.physicsSurfacePaintLimit.paintLimitOnPhysicsSurface, 0, 1);

	applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnRedChannel = UKismetMathLibrary::FClamp(applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnRedChannel, 0, 1);
	applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnGreenChannel = UKismetMathLibrary::FClamp(applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnGreenChannel, 0, 1);
	applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnBlueChannel = UKismetMathLibrary::FClamp(applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnBlueChannel, 0, 1);
	applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnAlphaChannel = UKismetMathLibrary::FClamp(applyColorSetting.vertexColorChannelsPaintLimit.paintLimitOnAlphaChannel, 0, 1);

	return applyColorSetting;
}


//--------------------------------------------------------

// Get Vertex Paint Game Instance Subsystem

UVertexPaintDetectionGISubSystem* VertexPaintFunctions::GetVertexPaintGameInstanceSubsystem(const UObject* WorldContextObject) {

	if (!IsValid(WorldContextObject)) return nullptr;
	if (!IsValid(UGameplayStatics::GetGameInstance(WorldContextObject))) return nullptr;
	if (!IsValid(UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UVertexPaintDetectionGISubSystem>())) return nullptr;


	return UGameplayStatics::GetGameInstance(WorldContextObject)->GetSubsystem<UVertexPaintDetectionGISubSystem>();
}


//--------------------------------------------------------

// Get Mesh Painted Since Session Started

TMap<UPrimitiveComponent*, int> VertexPaintFunctions::GetMeshPaintedSinceSessionStarted_Wrapper(const UObject* WorldContextObject) {

	if (!IsValid(GetVertexPaintGameInstanceSubsystem(WorldContextObject))) return TMap<UPrimitiveComponent*, int>();

	return GetVertexPaintGameInstanceSubsystem(WorldContextObject)->GetMeshPaintedSinceSessionStarted();
}


//--------------------------------------------------------

// Clear Mesh Painted Since Session Started

void VertexPaintFunctions::ClearMeshPaintedSinceSessionStarted_Wrapper(const UObject* WorldContextObject) {

	if (!IsValid(GetVertexPaintGameInstanceSubsystem(WorldContextObject))) return;


	GetVertexPaintGameInstanceSubsystem(WorldContextObject)->ClearMeshPaintedSinceSessionStarted();
}


//-------------------------------------------------------

// Get Calculate Colors Paint Task Amount

TMap<UPrimitiveComponent*, int> VertexPaintFunctions::GetCalculateColorsPaintTasksAmount_Wrapper(const UObject* WorldContextObject) {

	if (!IsValid(GetVertexPaintGameInstanceSubsystem(WorldContextObject))) return TMap<UPrimitiveComponent*, int>();


	if (GetVertexPaintTaskQueue(WorldContextObject))
		return GetVertexPaintTaskQueue(WorldContextObject)->GetCalculateColorsPaintTasksAmountPerComponent();

	return TMap<UPrimitiveComponent*, int>();
}


//-------------------------------------------------------

// Get Calculate Colors Detection Task Amount

TMap<UPrimitiveComponent*, int> VertexPaintFunctions::GetCalculateColorsDetectionTasksAmount_Wrapper(const UObject* WorldContextObject) {

	if (!IsValid(GetVertexPaintGameInstanceSubsystem(WorldContextObject))) return TMap<UPrimitiveComponent*, int>();


	if (GetVertexPaintTaskQueue(WorldContextObject))
		return GetVertexPaintTaskQueue(WorldContextObject)->GetCalculateColorsDetectionTasksAmountPerComponent();

	return TMap<UPrimitiveComponent*, int>();
}


//--------------------------------------------------------

// Get All Available Color Snippets on Mesh

void VertexPaintFunctions::GetAllMeshColorSnippetsAsString_Wrapper(UPrimitiveComponent* meshComponent, TMap<FString, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>>& availableColorSnippetsAndDataAssets) {

	availableColorSnippetsAndDataAssets.Empty();

	if (!IsValid(meshComponent)) return;


	auto colorSnippetReferenceDataAsset = GetColorSnippetReferenceDataAsset(meshComponent);

	if (!colorSnippetReferenceDataAsset) {

		UE_LOG(LogTemp, Warning, TEXT("VertexPaint - GetAllAvailableColorSnippetsOnMesh Fail because there's no Color Snippet Reference Data Asset Set in Settings so we can't get color snippet data assets a mesh has!"));

		return;
	}


	TMap<FString, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> colorSnippets_Local;

	if (auto staticMeshComp_Local = Cast<UStaticMeshComponent>(meshComponent)) {

		colorSnippets_Local = colorSnippetReferenceDataAsset->GetAllColorSnippetsAndDataAssetForObject(staticMeshComp_Local->GetStaticMesh());
	}

	else if (auto skeletalMeshComponent_Local = Cast<USkeletalMeshComponent>(meshComponent)) {

		const UObject* meshAsset_Local = VertexPaintFunctions::GetMeshComponentSourceMesh(skeletalMeshComponent_Local);

		colorSnippets_Local = colorSnippetReferenceDataAsset->GetAllColorSnippetsAndDataAssetForObject(meshAsset_Local);
	}

	// If is stored on a data asset
	if (colorSnippets_Local.Num() > 0)
		availableColorSnippetsAndDataAssets = colorSnippets_Local;
}


//--------------------------------------------------------

// Get All Available Color Snippets Tags on Mesh

void VertexPaintFunctions::GetAllMeshColorSnippetsAsTags_Wrapper(UPrimitiveComponent* meshComponent, TMap<FGameplayTag, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>>& availableColorSnippetTagsAndDataAssets) {

	availableColorSnippetTagsAndDataAssets.Empty();

	if (!IsValid(meshComponent) || !GetColorSnippetReferenceDataAsset(meshComponent)) return;


	TMap<FString, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> availableColorSnippetsAndDataAssets;
	GetAllMeshColorSnippetsAsString_Wrapper(meshComponent, availableColorSnippetsAndDataAssets);


	if (availableColorSnippetsAndDataAssets.Num() > 0) {

		TArray<FString> availableColorSnippets_Local;
		availableColorSnippetsAndDataAssets.GetKeys(availableColorSnippets_Local);

		TArray<TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> colorSnippetDataAssets_Local;
		availableColorSnippetsAndDataAssets.GenerateValueArray(colorSnippetDataAssets_Local);


		FGameplayTag topLevelTag = FGameplayTag::RequestGameplayTag(FName("ColorSnippets"));
		FGameplayTagContainer tagContainerTemp;
		tagContainerTemp.AddTag(FGameplayTag::RequestGameplayTag(topLevelTag.GetTagName(), false));
		FGameplayTagContainer tagContainer_Local = GetColorSnippetReferenceDataAsset(meshComponent)->allAvailableColorSnippets.Filter(tagContainerTemp);


		TArray<FGameplayTag> allAvailableTagsUnderCategory_Local;
		tagContainer_Local.GetGameplayTagArray(allAvailableTagsUnderCategory_Local);


		for (auto tag : allAvailableTagsUnderCategory_Local) {

			// If Mesh has Snippet ID that matches Tag under category 
			if (availableColorSnippets_Local.Contains(tag.GetTagName().ToString())) {

				int arrayIndex = -1;

				availableColorSnippets_Local.Find(tag.GetTagName().ToString(), arrayIndex);

				if (colorSnippetDataAssets_Local.IsValidIndex(arrayIndex))
					availableColorSnippetTagsAndDataAssets.Add(tag, colorSnippetDataAssets_Local[arrayIndex]);
			}
		}
	}
}


//--------------------------------------------------------

// Get All Mesh Color Snippets Tags Under Tag Category

void VertexPaintFunctions::GetAllMeshColorSnippetsTagsUnderTagCategory_Wrapper(UPrimitiveComponent* meshComponent, FGameplayTag tagCategory, TMap<FGameplayTag, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>>& availableColorSnippetTagsAndDataAssetsUnderTagCategory) {

	availableColorSnippetTagsAndDataAssetsUnderTagCategory.Empty();

	if (!IsValid(meshComponent) || !GetColorSnippetReferenceDataAsset(meshComponent)) return;


	TMap<FGameplayTag, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> availableColorSnippetTagsAndDataAssets;
	GetAllMeshColorSnippetsAsTags_Wrapper(meshComponent, availableColorSnippetTagsAndDataAssets);

	TArray<FGameplayTag> availableColorSnippetTags_Local;
	availableColorSnippetTagsAndDataAssets.GetKeys(availableColorSnippetTags_Local);

	TArray<TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> colorSnippetDataAssets_Local;
	availableColorSnippetTagsAndDataAssets.GenerateValueArray(colorSnippetDataAssets_Local);


	FGameplayTagContainer tagContainerTemp;
	tagContainerTemp.AddTag(FGameplayTag::RequestGameplayTag(tagCategory.GetTagName(), false));
	FGameplayTagContainer tagContainer_Local = GetColorSnippetReferenceDataAsset(meshComponent)->allAvailableColorSnippets.Filter(tagContainerTemp);

	TArray<FGameplayTag> allAvailableTagsUnderCategory_Local;
	tagContainer_Local.GetGameplayTagArray(allAvailableTagsUnderCategory_Local);


	for (auto tag : allAvailableTagsUnderCategory_Local) {

		// If Mesh has Snippet Tag that matches Tag under category 
		if (availableColorSnippetTags_Local.Contains(tag)) {

			int arrayIndex = -1;
			availableColorSnippetTags_Local.Find(tag, arrayIndex);

			if (colorSnippetDataAssets_Local.IsValidIndex(arrayIndex))
				availableColorSnippetTagsAndDataAssetsUnderTagCategory.Add(tag, colorSnippetDataAssets_Local[arrayIndex]);
		}
	}
}


//--------------------------------------------------------

// Get Mesh Color Snippets Tags In Tag Category

void VertexPaintFunctions::GetMeshColorSnippetsTagsInTagCategory_Wrapper(UPrimitiveComponent* meshComponent, FGameplayTag tagCategory, TMap<FGameplayTag, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>>& availableColorSnippetTagsAndDataAssetsUnderTagCategory) {

	availableColorSnippetTagsAndDataAssetsUnderTagCategory.Empty();

	if (!IsValid(meshComponent) || !GetColorSnippetReferenceDataAsset(meshComponent)) return;


	TMap<FGameplayTag, TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> availableColorSnippetTagsAndDataAssets;
	GetAllMeshColorSnippetsAsTags_Wrapper(meshComponent, availableColorSnippetTagsAndDataAssets);

	TArray<FGameplayTag> availableColorSnippetTags_Local;
	availableColorSnippetTagsAndDataAssets.GetKeys(availableColorSnippetTags_Local);

	TArray<TSoftObjectPtr<UVertexPaintColorSnippetDataAsset>> colorSnippetDataAssets_Local;
	availableColorSnippetTagsAndDataAssets.GenerateValueArray(colorSnippetDataAssets_Local);


	FGameplayTagContainer tagContainerTemp;
	tagContainerTemp.AddTag(FGameplayTag::RequestGameplayTag(tagCategory.GetTagName(), false));

	FGameplayTagContainer tagContainer_Local = GetColorSnippetReferenceDataAsset(meshComponent)->allAvailableColorSnippets.Filter(tagContainerTemp);
	TArray<FGameplayTag> allAvailableTagsUnderCategory_Local;
	tagContainer_Local.GetGameplayTagArray(allAvailableTagsUnderCategory_Local);


	for (auto tag : allAvailableTagsUnderCategory_Local) {

		FString tagAsString = tag.GetTagName().ToString();

		// Plus 1 so we don't have the . after the parent category
		FString tagStringWithoutParentCategory = tagAsString.RightChop(tagCategory.GetTagName().ToString().Len() + 1);

		int charIndexWithPeriod = -1;

		// If has a ., i.e. this is not tag that is directly in the tag category but another under that. 
		if (tagStringWithoutParentCategory.FindChar('.', charIndexWithPeriod))
			continue;


		// If Mesh has Snippet Tag that matches Tag under category 
		if (availableColorSnippetTags_Local.Contains(tag)) {

			int arrayIndex = -1;
			availableColorSnippetTags_Local.Find(tag, arrayIndex);

			if (colorSnippetDataAssets_Local.IsValidIndex(arrayIndex))
				availableColorSnippetTagsAndDataAssetsUnderTagCategory.Add(tag, colorSnippetDataAssets_Local[arrayIndex]);
		}
	}
}


//--------------------------------------------------------

// Get Color Snippet Reference Data Asset

UVertexPaintColorSnippetRefs* VertexPaintFunctions::GetColorSnippetReferenceDataAsset(const UObject* optionalWorldContextObject) {



	if (optionalWorldContextObject) {

		if (auto gameInstanceSubsystem = GetVertexPaintGameInstanceSubsystem(optionalWorldContextObject))
			return gameInstanceSubsystem->GetCachedColorSnippetReferenceDataAsset();
	}

	// If can't provide a valid world we can still get it if in game thread. But if async then we need a valid world so we can get the cached one since it's not safe to run .Get() and ofc. LoadSynchronous in async. 
	if (IsInGameThread()) {

		if (auto vertexPaintDetectionSettings_Local = GetDefault<UVertexPaintDetectionSettings>())
			return vertexPaintDetectionSettings_Local->VertexPaintFunctionsLib_ColorSnippetReferencesDataAssetToUse.LoadSynchronous();
	}

	return nullptr;
}


//--------------------------------------------------------

// Get Optimization Data Asset

UVertexPaintOptimizationDataAsset* VertexPaintFunctions::GetOptimizationDataAsset(const UObject* optionalWorldContextObject) {


	if (optionalWorldContextObject) {

		if (auto gameInstanceSubsystem = GetVertexPaintGameInstanceSubsystem(optionalWorldContextObject))
			return gameInstanceSubsystem->GetCachedOptimizationDataAsset();
	}

	// If can't provide a valid world we can still get it if in game thread. But if async then we need a valid world so we can get the cached one since it's not safe to run .Get() and ofc. LoadSynchronous in async. 
	if (IsInGameThread()) {

		if (auto vertexPaintDetectionSettings_Local = GetDefault<UVertexPaintDetectionSettings>())
			return vertexPaintDetectionSettings_Local->VertexPaintFunctionsLib_OptimizationDataAssetToUse.LoadSynchronous();
	}

	return nullptr;
}


//--------------------------------------------------------

// Get Vertex Paint Material Data Asset

UVertexPaintMaterialDataAsset* VertexPaintFunctions::GetVertexPaintMaterialDataAsset(const UObject* optionalWorldContextObject) {


	if (optionalWorldContextObject && IsWorldValid(optionalWorldContextObject->GetWorld())) {

		if (auto gameInstanceSubsystem = GetVertexPaintGameInstanceSubsystem(optionalWorldContextObject))
			return gameInstanceSubsystem->GetCachedMaterialDataAsset();
	}

	// If can't provide a valid world we can still get it if in game thread. But if async then we need a valid world so we can get the cached one since it's not safe to run .Get() and ofc. LoadSynchronous in async. 
	if (IsInGameThread()) {

		if (auto vertexPaintDetectionSettings_Local = GetDefault<UVertexPaintDetectionSettings>())
			return vertexPaintDetectionSettings_Local->VertexPaintFunctionsLib_MaterialsDataAssetToUse.LoadSynchronous();
	}

	return nullptr;
}


//-------------------------------------------------------

// Get Max LOD To Paint On

int VertexPaintFunctions::GetAmountOfLODsToPaintOn(UPrimitiveComponent* meshComp, bool overrideLODToPaintUpOn, int overrideUpToLOD) {

	if (!IsValid(meshComp)) return 1;


	int lodsToPaint_Local = 1;
	int maxLODsAvailable_Local = 1;


	if (auto staticMesh_Local = Cast<UStaticMeshComponent>(meshComp)) {

		if (!staticMesh_Local->GetStaticMesh()) return 1;
		if (!staticMesh_Local->GetStaticMesh()->GetRenderData()) return 1;

		maxLODsAvailable_Local = staticMesh_Local->GetStaticMesh()->GetRenderData()->LODResources.Num();

		lodsToPaint_Local = maxLODsAvailable_Local;


		if (auto optimizationDataAssetTemp = GetOptimizationDataAsset(meshComp)) {

			// If the mesh is added to only be painted a certain number of LODs in the Optimization Data Asset 
			if (optimizationDataAssetTemp->GetStaticMeshNumOfLODsToPaint().Contains(staticMesh_Local->GetStaticMesh())) {

				int LODsLimitToPaint_Local = optimizationDataAssetTemp->GetStaticMeshNumOfLODsToPaint().FindRef(staticMesh_Local->GetStaticMesh()).maxAmountOfLODsToPaint;


				if (LODsLimitToPaint_Local <= maxLODsAvailable_Local)
					lodsToPaint_Local = LODsLimitToPaint_Local;
			}
		}


		if (overrideLODToPaintUpOn) {

			if (maxLODsAvailable_Local >= overrideUpToLOD) {

				return overrideUpToLOD;
			}

			else {

				// If lodsToPaint_Local was less than override LOD, then just returns the maximum LODs we have so we get as close to the Override LOD 
				return maxLODsAvailable_Local;
			}
		}

		return lodsToPaint_Local;
	}

	else if (auto skeletalMeshComp_Local = Cast<USkeletalMeshComponent>(meshComp)) {


		USkeletalMesh* skelMesh_Local = nullptr;

#if ENGINE_MAJOR_VERSION == 4

		skelMesh_Local = skeletalMeshComp_Local->SkeletalMesh;

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

		skelMesh_Local = skeletalMeshComp_Local->SkeletalMesh.Get();

#else

		skelMesh_Local = skeletalMeshComp_Local->GetSkeletalMeshAsset();

#endif
#endif

		if (!skelMesh_Local) return 1;
		if (!skeletalMeshComp_Local->GetSkeletalMeshRenderData()) return 1;


		maxLODsAvailable_Local = skeletalMeshComp_Local->GetSkeletalMeshRenderData()->LODRenderData.Num();

		lodsToPaint_Local = maxLODsAvailable_Local;


		if (auto optimizationDataAssetTemp = GetOptimizationDataAsset(meshComp)) {

			if (optimizationDataAssetTemp->GetSkeletalMeshNumOfLODsToPaint().Contains(skelMesh_Local)) {

				int LODsLimitToPaint_Local = optimizationDataAssetTemp->GetSkeletalMeshNumOfLODsToPaint().FindRef(skelMesh_Local).maxAmountOfLODsToPaint;

				if (LODsLimitToPaint_Local <= maxLODsAvailable_Local)
					lodsToPaint_Local = LODsLimitToPaint_Local;
			}
		}


		if (overrideLODToPaintUpOn) {

			if (maxLODsAvailable_Local >= overrideUpToLOD) {

				return overrideUpToLOD;
			}

			else {

				return maxLODsAvailable_Local;
			}
		}

		return lodsToPaint_Local;
	}

	return 1;
}


//--------------------------------------------------------

// Multisphere Trace For Paint At Location

void VertexPaintFunctions::MultiCapsuleTraceForClosestUniqueMeshes_Wrapper(const UObject* WorldContextObject, FVector location, float radius, ETraceTypeQuery traceChannel, const TArray<TEnumAsByte<EObjectTypeQuery>>& objectTypesToTraceFor, const TArray<AActor*>& actorsToIgnore, EDrawDebugTrace::Type drawDebugType, TArray<FHitResult>& closestHitsWithUniqueMeshes, float debugDrawTime, bool ignoreSelf, bool traceComplex) {

	closestHitsWithUniqueMeshes.Empty();

	if (!WorldContextObject) return;
	if (!WorldContextObject->GetWorld()) return;
	if (radius <= 0) return;


	// For UE4 it doesn't work to get the face index even if traceComplex is set to True, so turns it off here. 
#if ENGINE_MAJOR_VERSION == 4
	traceComplex = false;
#endif


	TArray<FHitResult> hitResults_Local;

	// Capsule Trace either with objects or visibility so we could get the Face Index. Wasn't posible with Sphere Trace. If we've set object types then traces with that. 
	if (objectTypesToTraceFor.Num() > 0) {

		UKismetSystemLibrary::CapsuleTraceMultiForObjects(WorldContextObject->GetWorld(), location, location * 1.00001f, radius, radius, objectTypesToTraceFor, traceComplex, actorsToIgnore, drawDebugType, hitResults_Local, ignoreSelf, FLinearColor::Red, FLinearColor::Green, debugDrawTime);
	}
	else {

		UKismetSystemLibrary::CapsuleTraceMulti(WorldContextObject->GetWorld(), location, location * 1.00001f, radius, radius, traceChannel, traceComplex, actorsToIgnore, drawDebugType, hitResults_Local, ignoreSelf, FLinearColor::Red, FLinearColor::Green, debugDrawTime);
	}


	if (hitResults_Local.Num() > 0) {

		TMap<UPrimitiveComponent*, FHitResult> hitResultWithUniqueMeshes_Local;
		TMap<UPrimitiveComponent*, float> closestDistances_Local;


		// Makes sure we only get one from each mesh and the closest hit
		for (int i = 0; i < hitResults_Local.Num(); i++) {

			if (IsValid(hitResults_Local[i].Component.Get())) {

				float distance_Local = (hitResults_Local[i].Location - location).Size();


				if (hitResultWithUniqueMeshes_Local.Contains(hitResults_Local[i].Component.Get())) {

					// If mesh already been added, but this hit is closer, then updates it
					if (distance_Local < closestDistances_Local.FindRef(hitResults_Local[i].Component.Get())) {

						closestDistances_Local.Add(hitResults_Local[i].Component.Get(), distance_Local);
						hitResultWithUniqueMeshes_Local.Add(hitResults_Local[i].Component.Get(), hitResults_Local[i]);
					}
				}

				else {

					closestDistances_Local.Add(hitResults_Local[i].Component.Get(), distance_Local);
					hitResultWithUniqueMeshes_Local.Add(hitResults_Local[i].Component.Get(), hitResults_Local[i]);
				}
			}
		}

		hitResultWithUniqueMeshes_Local.GenerateValueArray(closestHitsWithUniqueMeshes);
	}
}


//--------------------------------------------------------

// Set Static Mesh And Release Override Vertex Colors

void VertexPaintFunctions::VertexPaintFunctionsLib_SetStaticMeshAndReleaseOverrideVertexColors(UStaticMeshComponent* staticMeshComponent, UStaticMesh* newMesh) {

	if (!IsValid(staticMeshComponent) || !IsValid(newMesh)) return;


	// Necessary otherwise it had the same amount of LODs as the previous static mesh
	staticMeshComponent->SetLODDataCount(newMesh->GetNumLODs(), newMesh->GetNumLODs());

	if (staticMeshComponent->LODData.Num() > 0) {

		for (int i = 0; i < staticMeshComponent->LODData.Num(); i++) {


			int amountOfVertsToSwitchTo = 0;
			TArray<FColor> colorLOD_Local;

			if (newMesh->GetRenderData()->LODResources.IsValidIndex(i)) {

				amountOfVertsToSwitchTo = newMesh->GetRenderData()->LODResources[i].GetNumVertices();
				auto colVertBufferAtLOD_Local = &newMesh->GetRenderData()->LODResources[i].VertexBuffers.ColorVertexBuffer;

				// If color buffer isn't initialized it means its default colors are White and it hasn't been painted either in editor or in runtime, if this is the case we init the array with white so even unstored, unpainted cpu meshes with all default white vertex colors can be painted and look as they should. 
				if (colVertBufferAtLOD_Local) {

					if (colVertBufferAtLOD_Local->IsInitialized())
						colorLOD_Local.Init(FColor(0, 0, 0, 0), amountOfVertsToSwitchTo);
					else
						colorLOD_Local.Init(FColor::White, amountOfVertsToSwitchTo);
				}

				else {

					colorLOD_Local.Init(FColor::White, amountOfVertsToSwitchTo);
				}
			}

			// Had to make a new color vertex buffer and init it, otherwise when switching mesh, the new mesh could get really weird colors, as if the old buffer "bleed" to the next mesh but where the vertex color didn't match since it's a new mesh with different vertex amount etc. 
			staticMeshComponent->LODData[i].OverrideVertexColors = new FColorVertexBuffer();
			staticMeshComponent->LODData[i].OverrideVertexColors->InitFromColorArray(colorLOD_Local);
			BeginInitResource(staticMeshComponent->LODData[i].OverrideVertexColors);
		}
	}

	staticMeshComponent->SetStaticMesh(newMesh);

	staticMeshComponent->MarkRenderStateDirty();


}


//--------------------------------------------------------

// Release Resources And Set Skeletal Mesh

void VertexPaintFunctions::VertexPaintFunctionsLib_SetSkeletalMeshAndReleaseResources(USkeletalMeshComponent* skeletalMeshComponent, USkeletalMesh* newMesh) {

	if (!IsValid(skeletalMeshComponent) || !IsValid(newMesh)) return;


	USkeletalMesh* skelMeshTemp = nullptr;

#if ENGINE_MAJOR_VERSION == 4

	skelMeshTemp = skeletalMeshComponent->SkeletalMesh;

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

	skelMeshTemp = skeletalMeshComponent->SkeletalMesh.Get();

#else

	skelMeshTemp = skeletalMeshComponent->GetSkeletalMeshAsset();

#endif

#endif


	skeletalMeshComponent->ReleaseResources(); // Fixes so we don't get crash if we're applying colors to the skeletal mesh and switching


	// When i tested painting every single frame and switching characters like crazy i once still got a crash when running SetSkeletalMesh(), with trying to delete vertex color buffer before releasing it or something. So added all these to really make sure everything gets released before we switch


	skeletalMeshComponent->ReleaseAllClothingResources();

	for (int i = 0; i < skeletalMeshComponent->LODInfo.Num(); i++) {

		skeletalMeshComponent->ClearVertexColorOverride(i);
		skeletalMeshComponent->LODInfo[i].BeginReleaseOverrideVertexColors();
		skeletalMeshComponent->LODInfo[i].ReleaseOverrideVertexColorsAndBlock();
	}

	if (skelMeshTemp)
		skelMeshTemp->ReleaseResourcesFence.Wait();

	//----------

#if ENGINE_MAJOR_VERSION == 4

	skeletalMeshComponent->SetSkeletalMesh(newMesh, false);

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

	skeletalMeshComponent->SetSkeletalMesh(newMesh, false);

#else

	skeletalMeshComponent->SetSkeletalMeshAsset(newMesh);

#endif

#endif
}


//--------------------------------------------------------

// Sort String Array Alphabetically

TArray<FString> VertexPaintFunctions::VertexPaintFunctionsLib_SortStringArrayAlphabetically(TArray<FString> strings) {

	FString tempString;

	for (int i = 0; i < strings.Num(); ++i) {

		for (int j = i + 1; j < strings.Num(); ++j) {

			if (strings[i] > strings[j]) {

				tempString = strings[i];
				strings[i] = strings[j];
				strings[j] = tempString;
			}
		}
	}

	return strings;
}


//--------------------------------------------------------

// Sort Assets Names Alphabetically

TMap<int, FString> VertexPaintFunctions::VertexPaintFunctionsLib_SortAssetsNamesAlphabetically(TMap<int, FString> assetIndexAndName) {


	FString name_Local;
	TArray<FString> names_Local;
	assetIndexAndName.GenerateValueArray(names_Local);

	int index_Local;
	TArray<int> indexes_Local;
	assetIndexAndName.GetKeys(indexes_Local);


	for (int i = 0; i < names_Local.Num(); ++i) {

		for (int j = i + 1; j < names_Local.Num(); ++j) {

			if (names_Local[i] > names_Local[j]) {

				name_Local = names_Local[i];
				index_Local = indexes_Local[i];

				names_Local[i] = names_Local[j];
				indexes_Local[i] = indexes_Local[j];

				names_Local[j] = name_Local;
				indexes_Local[j] = index_Local;
			}
		}
	}

	TMap<int, FString> indexesAndTheirName_Local;

	for (int i = 0; i < indexes_Local.Num(); i++) {

		indexesAndTheirName_Local.Add(indexes_Local[i], names_Local[i]);
	}

	return indexesAndTheirName_Local;
}


//--------------------------------------------------------

// Draw Primitive Bounds Box

void VertexPaintFunctions::DrawPrimitiveComponentBoundsBox(UPrimitiveComponent* component, float lifetime, float thickness, FLinearColor colorToDraw) {

	if (!IsInGameThread()) return;
	if (!IsValid(component)) return;
	if (!IsValid(component->GetWorld())) return;
	if (!component->GetWorld()->IsGameWorld()) return;
	if (component->GetWorld()->bIsTearingDown) return;


	if (Cast<USkeletalMeshComponent>(component)) {

		DrawDebugBox(component->GetWorld(), component->Bounds.GetBox().GetCenter(), component->Bounds.GetBox().GetExtent(), colorToDraw.ToFColor(false), false, lifetime, 0, thickness);
	}

	// In order to take the added collision of static meshes into account we had to get the AggGeom
	else if (Cast<UStaticMeshComponent>(component)) {

		FBoxSphereBounds AggGeomBounds;
		component->GetBodySetup()->AggGeom.CalcBoxSphereBounds(AggGeomBounds, component->GetComponentToWorld());

		DrawDebugBox(component->GetWorld(), component->Bounds.GetBox().GetCenter(), AggGeomBounds.GetBox().GetExtent(), colorToDraw.ToFColor(false), false, lifetime, 0, thickness);
	}
}


//--------------------------------------------------------

// Get Amount Of Painted Colors For Each Channel - Async Version

bool VertexPaintFunctions::isGetAmountOfPaintedColorsForEachChannelAsyncTaskRunning = false;

void VertexPaintFunctions::GetAmountOfPaintedColorsForEachChannelAsync(UObject* WorldContextObject, FLatentActionInfo LatentInfo, const TArray<FColor>& vertexColors, float minColorAmountToBeConsidered, FVertexDetectAmountOfPaintedColorsOfEachChannel& amountOfColorsOfEachChannel) {

	if (isGetAmountOfPaintedColorsForEachChannelAsyncTaskRunning) {

		UE_LOG(LogTemp, Log, TEXT("Trying to Start GetAmountOfPaintedColorsForEachChannelAsync but it already has a Task awaiting to be Finished!"));
		return;
	}


	if (UWorld* World = WorldContextObject->GetWorld()) {

		// Instantiate the AsyncTask
		FColorsOfEachChannelAsyncTask* calculateColorsOfEachChannelAsyncTask = new FColorsOfEachChannelAsyncTask(vertexColors, minColorAmountToBeConsidered);

		// Create our custom latent action and add to manager
		FColorsOfEachChannelLatentAction* LatentAction = new FColorsOfEachChannelLatentAction(LatentInfo, calculateColorsOfEachChannelAsyncTask);
		World->GetLatentActionManager().AddNewAction(LatentInfo.CallbackTarget, LatentInfo.UUID, LatentAction);

		// Bind the delegate and sets the result
		calculateColorsOfEachChannelAsyncTask->OnTaskComplete.BindLambda([&amountOfColorsOfEachChannel, LatentAction](const FVertexDetectAmountOfPaintedColorsOfEachChannel& amountOfPaintedColorsOfEachChannelResult) {

			amountOfColorsOfEachChannel = amountOfPaintedColorsOfEachChannelResult;
			isGetAmountOfPaintedColorsForEachChannelAsyncTaskRunning = false;

			LatentAction->MarkAsCompleted();
		});

		isGetAmountOfPaintedColorsForEachChannelAsyncTaskRunning = true;

		(new FAutoDeleteAsyncTask<FColorsOfEachChannelAsyncTask>(*calculateColorsOfEachChannelAsyncTask))->StartBackgroundTask();
	}
}


//--------------------------------------------------------

// Get Amount Of Painted Colors For Each Channel

FVertexDetectAmountOfPaintedColorsOfEachChannel VertexPaintFunctions::GetAmountOfPaintedColorsForEachChannel(const TArray<FColor>& vertexColors, float minColorAmountToBeConsidered) {

	if (vertexColors.Num() <= 0) return FVertexDetectAmountOfPaintedColorsOfEachChannel();


	FVertexDetectAmountOfPaintedColorsOfEachChannel amountOfPaintedColorsOfEachChannel_Local;
	FLinearColor linearColor_Local;


	for (auto colorTemp : vertexColors) {

		linearColor_Local = colorTemp.ReinterpretAsLinear(); // So we only have to run Reinterpret once


		// These are used by the async task to check if even the vertex channel was considered, since with paint/detect task you have option to only include those that has a physics surface registered to them, and if they're not, they won't even be considered and if none where considered we didn't run any more logic in FillAmountOfPaintedColorsOfEachChannel()
		amountOfPaintedColorsOfEachChannel_Local.redChannelResult.amountOfVerticesConsidered++;
		amountOfPaintedColorsOfEachChannel_Local.greenChannelResult.amountOfVerticesConsidered++;
		amountOfPaintedColorsOfEachChannel_Local.blueChannelResult.amountOfVerticesConsidered++;
		amountOfPaintedColorsOfEachChannel_Local.alphaChannelResult.amountOfVerticesConsidered++;


		if (linearColor_Local.R >= minColorAmountToBeConsidered) {

			amountOfPaintedColorsOfEachChannel_Local.redChannelResult.amountOfVerticesPaintedAtMinAmount++;
			amountOfPaintedColorsOfEachChannel_Local.redChannelResult.averageColorAmountAtMinAmount += linearColor_Local.R;
		}
		if (linearColor_Local.G >= minColorAmountToBeConsidered) {

			amountOfPaintedColorsOfEachChannel_Local.greenChannelResult.amountOfVerticesPaintedAtMinAmount++;
			amountOfPaintedColorsOfEachChannel_Local.greenChannelResult.averageColorAmountAtMinAmount += linearColor_Local.G;
		}
		if (linearColor_Local.B >= minColorAmountToBeConsidered) {

			amountOfPaintedColorsOfEachChannel_Local.blueChannelResult.amountOfVerticesPaintedAtMinAmount++;
			amountOfPaintedColorsOfEachChannel_Local.blueChannelResult.averageColorAmountAtMinAmount += linearColor_Local.B;
		}
		if (linearColor_Local.A >= minColorAmountToBeConsidered) {

			amountOfPaintedColorsOfEachChannel_Local.alphaChannelResult.amountOfVerticesPaintedAtMinAmount++;
			amountOfPaintedColorsOfEachChannel_Local.alphaChannelResult.averageColorAmountAtMinAmount += linearColor_Local.A;
		}
	}

	// After gotten amount of vertices painted at each color etc., we can use it to set the amounts. This is used by the async task as well
	amountOfPaintedColorsOfEachChannel_Local = ConsolidateColorsOfEachChannel(amountOfPaintedColorsOfEachChannel_Local, vertexColors.Num());


	return amountOfPaintedColorsOfEachChannel_Local;
}


//--------------------------------------------------------

// Set Mesh Constant Vertex Colors and Enables Them

UDynamicMesh* VertexPaintFunctions::SetMeshConstantVertexColorsAndEnablesThem(UDynamicMesh* TargetMesh, FLinearColor Color, FGeometryScriptColorFlags Flags, bool bClearExisting, UGeometryScriptDebug* Debug) {

	if (!TargetMesh) return nullptr;


	UE::Geometry::FDynamicMesh3* dynamicMesh3 = nullptr;
	dynamicMesh3 = &TargetMesh->GetMeshRef();

	if (dynamicMesh3) {

		// So we can run EnableVertexColors() again after. Otherwise it would only work once, because it returns if HasVertexColors is true, which created a problem if we painted or detected on the dynamic mesh (which enables colors if there aren't any), then ran this function, because then SetMeshConstantVertexColor() would run but we couldn't actually Set the colors to what SetMeshConstantVertexColor because EnableVertexColors just returned. 
		dynamicMesh3->DiscardVertexColors();

		UGeometryScriptLibrary_MeshVertexColorFunctions::SetMeshConstantVertexColor(TargetMesh, Color, Flags, bClearExisting, Debug);

		// Converts these like this instead of with .ToFColor since we could get issues where for instance a few vertices out of 10k got their color reset to 0. This fixed the issue. 
		FColor colorToApplyTemp;
		colorToApplyTemp.R = (uint8)UKismetMathLibrary::MapRangeClamped(Color.R, 0, 1, 0, 255);
		colorToApplyTemp.G = (uint8)UKismetMathLibrary::MapRangeClamped(Color.G, 0, 1, 0, 255);
		colorToApplyTemp.B = (uint8)UKismetMathLibrary::MapRangeClamped(Color.B, 0, 1, 0, 255);
		colorToApplyTemp.A = 0;

		dynamicMesh3->EnableVertexColors(FVector3f(colorToApplyTemp.R, colorToApplyTemp.G, colorToApplyTemp.B));
	}


	return TargetMesh;
}


//--------------------------------------------------------

// Consolidate Colors Of Each Channel

FVertexDetectAmountOfPaintedColorsOfEachChannel VertexPaintFunctions::ConsolidateColorsOfEachChannel(FVertexDetectAmountOfPaintedColorsOfEachChannel amountOfColorsOfEachChannel, int amountOfVertices) {

	if (amountOfVertices <= 0) return amountOfColorsOfEachChannel;

	// If haven't gotten anything on any channel then isn't successfull. 
	if (amountOfColorsOfEachChannel.redChannelResult.amountOfVerticesConsidered <= 0 && amountOfColorsOfEachChannel.greenChannelResult.amountOfVerticesConsidered <= 0 && amountOfColorsOfEachChannel.blueChannelResult.amountOfVerticesConsidered <= 0 && amountOfColorsOfEachChannel.alphaChannelResult.amountOfVerticesConsidered <= 0) return amountOfColorsOfEachChannel;


	amountOfColorsOfEachChannel.redChannelResult.averageColorAmountAtMinAmount = amountOfColorsOfEachChannel.redChannelResult.averageColorAmountAtMinAmount / amountOfVertices;
	amountOfColorsOfEachChannel.greenChannelResult.averageColorAmountAtMinAmount = amountOfColorsOfEachChannel.greenChannelResult.averageColorAmountAtMinAmount / amountOfVertices;
	amountOfColorsOfEachChannel.blueChannelResult.averageColorAmountAtMinAmount = amountOfColorsOfEachChannel.blueChannelResult.averageColorAmountAtMinAmount / amountOfVertices;
	amountOfColorsOfEachChannel.alphaChannelResult.averageColorAmountAtMinAmount = amountOfColorsOfEachChannel.alphaChannelResult.averageColorAmountAtMinAmount / amountOfVertices;


	amountOfColorsOfEachChannel.redChannelResult.percentPaintedAtMinAmount = amountOfColorsOfEachChannel.redChannelResult.amountOfVerticesPaintedAtMinAmount / amountOfVertices;
	amountOfColorsOfEachChannel.greenChannelResult.percentPaintedAtMinAmount = amountOfColorsOfEachChannel.greenChannelResult.amountOfVerticesPaintedAtMinAmount / amountOfVertices;
	amountOfColorsOfEachChannel.blueChannelResult.percentPaintedAtMinAmount = amountOfColorsOfEachChannel.blueChannelResult.amountOfVerticesPaintedAtMinAmount / amountOfVertices;
	amountOfColorsOfEachChannel.alphaChannelResult.percentPaintedAtMinAmount = amountOfColorsOfEachChannel.alphaChannelResult.amountOfVerticesPaintedAtMinAmount / amountOfVertices;

	amountOfColorsOfEachChannel.redChannelResult.percentPaintedAtMinAmount *= 100;
	amountOfColorsOfEachChannel.greenChannelResult.percentPaintedAtMinAmount *= 100;
	amountOfColorsOfEachChannel.blueChannelResult.percentPaintedAtMinAmount *= 100;
	amountOfColorsOfEachChannel.alphaChannelResult.percentPaintedAtMinAmount *= 100;

	amountOfColorsOfEachChannel.successfullyGotColorChannelResultsAtMinAmount = true;

	return amountOfColorsOfEachChannel;
}


//--------------------------------------------------------

// Consolidate Physics Surface Result

FVertexDetectAmountOfPaintedColorsOfEachChannel VertexPaintFunctions::ConsolidatePhysicsSurfaceResult(FVertexDetectAmountOfPaintedColorsOfEachChannel amountOfColorsOfEachChannel, int amountOfVertices) {

	if (amountOfVertices <= 0) return amountOfColorsOfEachChannel;
	if (amountOfColorsOfEachChannel.physicsSurfacesResult.Num() <= 0) return amountOfColorsOfEachChannel;


	for (auto& physicsSurfaceResultsTemp : amountOfColorsOfEachChannel.physicsSurfacesResult) {

		if (physicsSurfaceResultsTemp.Value.amountOfVerticesConsidered <= 0) continue;

		physicsSurfaceResultsTemp.Value.averageColorAmountAtMinAmount = physicsSurfaceResultsTemp.Value.averageColorAmountAtMinAmount / amountOfVertices;

		physicsSurfaceResultsTemp.Value.percentPaintedAtMinAmount = physicsSurfaceResultsTemp.Value.amountOfVerticesPaintedAtMinAmount / amountOfVertices;
		physicsSurfaceResultsTemp.Value.percentPaintedAtMinAmount *= 100;
	}


	// Create a TArray of pairs to hold the elements and their float values
	TArray<TPair<TEnumAsByte<EPhysicalSurface>, FVertexDetectAmountOfPaintedColorsOfEachChannel_Results>> SortedArray;
	for (const auto& Pair : amountOfColorsOfEachChannel.physicsSurfacesResult) {

		SortedArray.Add(TPair<TEnumAsByte<EPhysicalSurface>, FVertexDetectAmountOfPaintedColorsOfEachChannel_Results>(Pair.Key, Pair.Value));
	}

	// Sort the array based on painted percent
	SortedArray.Sort([](const TPair<TEnumAsByte<EPhysicalSurface>, FVertexDetectAmountOfPaintedColorsOfEachChannel_Results>& A, const TPair<TEnumAsByte<EPhysicalSurface>, FVertexDetectAmountOfPaintedColorsOfEachChannel_Results>& B) {
		return A.Value.percentPaintedAtMinAmount > B.Value.percentPaintedAtMinAmount;
		});

	TMap<TEnumAsByte<EPhysicalSurface>, FVertexDetectAmountOfPaintedColorsOfEachChannel_Results> sortedPhysicsSurfacesResultTemp;
	for (const auto& Pair : SortedArray) {

		sortedPhysicsSurfacesResultTemp.Add(Pair.Key, Pair.Value);
	}


	amountOfColorsOfEachChannel.physicsSurfacesResult = sortedPhysicsSurfacesResultTemp;
	amountOfColorsOfEachChannel.successfullyGotPhysicsSurfaceResultsAtMinAmount = true;

	return amountOfColorsOfEachChannel;
}


//--------------------------------------------------------

// Get Skeletal Mesh

USkeletalMesh* VertexPaintFunctions::VertexPaintFunctionsLib_GetSkeletalMesh(USkeletalMeshComponent* skeletalMeshComp) {

	if (!IsValid(skeletalMeshComp)) return nullptr;


#if ENGINE_MAJOR_VERSION == 4

	return skeletalMeshComp->SkeletalMesh;

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

	return skeletalMeshComp->SkeletalMesh.Get();

#else

	return skeletalMeshComp->GetSkeletalMeshAsset();

#endif
#endif

	return nullptr;
}


//--------------------------------------------------------

// Get Mesh Component Vertex Colors

FVertexDetectMeshDataStruct VertexPaintFunctions::GetMeshComponentVertexColors_Wrapper(UPrimitiveComponent* meshComponent, bool& success, bool getColorsForAllLODs, int getColorsUpToLOD) {

	success = false;
	if (!IsValid(meshComponent)) return FVertexDetectMeshDataStruct();
	if (!getColorsForAllLODs && getColorsUpToLOD < 0) return FVertexDetectMeshDataStruct();


	FVertexDetectMeshDataStruct vertexMeshData_Local;
	TArray<FVertexDetectMeshDataPerLODStruct> meshDataPerLod_Local;
	int amountOfLODsToGet = getColorsUpToLOD + 1;


	if (auto staticMeshComponent = Cast<UStaticMeshComponent>(meshComponent)) {

		if (!IsValid(staticMeshComponent->GetStaticMesh())) return FVertexDetectMeshDataStruct();


		vertexMeshData_Local.meshComp = staticMeshComponent;
		vertexMeshData_Local.meshSource = staticMeshComponent->GetStaticMesh();

		if (getColorsForAllLODs)
			amountOfLODsToGet = staticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources.Num();


		for (int i = 0; i < amountOfLODsToGet; i++) {

			FVertexDetectMeshDataPerLODStruct meshDataPerLodTemp;
			meshDataPerLodTemp.lod = i;
			meshDataPerLodTemp.meshVertexColorsPerLODArray = GetStaticMeshVertexColorsAtLOD(staticMeshComponent, i);

			// If actually got any colors, i.e. the lod was valid
			if (meshDataPerLodTemp.meshVertexColorsPerLODArray.Num() > 0)
				meshDataPerLod_Local.Add(meshDataPerLodTemp);
		}

		vertexMeshData_Local.meshDataPerLOD = meshDataPerLod_Local;
		success = true;

		return vertexMeshData_Local;
	}

	else if (auto skeletalMeshComponent = Cast<USkeletalMeshComponent>(meshComponent)) {

		const UObject* skelMesh = VertexPaintFunctions::GetMeshComponentSourceMesh(skeletalMeshComponent);

		if (!IsValid(skelMesh)) return FVertexDetectMeshDataStruct();


		vertexMeshData_Local.meshComp = skeletalMeshComponent;
		vertexMeshData_Local.meshSource = skelMesh;

		if (getColorsForAllLODs)
			amountOfLODsToGet = skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData.Num();


		for (int i = 0; i < amountOfLODsToGet; i++) {

			FVertexDetectMeshDataPerLODStruct meshDataPerLodTemp;
			meshDataPerLodTemp.lod = i;
			meshDataPerLodTemp.meshVertexColorsPerLODArray = GetSkeletalMeshVertexColorsAtLOD(skeletalMeshComponent, i);

			// If actually got any colors, i.e. the lod was valid
			if (meshDataPerLodTemp.meshVertexColorsPerLODArray.Num() > 0)
				meshDataPerLod_Local.Add(meshDataPerLodTemp);
		}

		vertexMeshData_Local.meshDataPerLOD = meshDataPerLod_Local;
		success = true;

		return vertexMeshData_Local;
	}

#if ENGINE_MAJOR_VERSION == 5

	else if (auto dynamicMeshComponent = Cast<UDynamicMeshComponent>(meshComponent)) {

		vertexMeshData_Local.meshComp = dynamicMeshComponent;
		// vertexMeshData_Local.meshSource = ;

		FVertexDetectMeshDataPerLODStruct meshDataPerLodTemp;
		meshDataPerLodTemp.lod = 0;
		meshDataPerLodTemp.meshVertexColorsPerLODArray = GetDynamicMeshVertexColors(dynamicMeshComponent);

		// If actually got any colors, i.e. the lod was valid
		if (meshDataPerLodTemp.meshVertexColorsPerLODArray.Num() > 0)
			meshDataPerLod_Local.Add(meshDataPerLodTemp);

		vertexMeshData_Local.meshDataPerLOD = meshDataPerLod_Local;
		success = true;
	}

	else if (auto geometryCollectionComponent = Cast<UGeometryCollectionComponent>(meshComponent)) {


		vertexMeshData_Local.meshComp = geometryCollectionComponent;
		vertexMeshData_Local.meshSource = geometryCollectionComponent->GetRestCollection();

		FVertexDetectMeshDataPerLODStruct meshDataPerLodTemp;
		meshDataPerLodTemp.lod = 0;
		meshDataPerLodTemp.meshVertexColorsPerLODArray = GetGeometryCollectionVertexColors(geometryCollectionComponent);

		// If actually got any colors, i.e. the lod was valid
		if (meshDataPerLodTemp.meshVertexColorsPerLODArray.Num() > 0)
			meshDataPerLod_Local.Add(meshDataPerLodTemp);

		vertexMeshData_Local.meshDataPerLOD = meshDataPerLod_Local;
		success = true;
	}

#endif

	return FVertexDetectMeshDataStruct();
}


//--------------------------------------------------------

// Get Mesh Component Vertex Colors At Specific LOD

TArray<FColor> VertexPaintFunctions::GetMeshComponentVertexColorsAtLOD_Wrapper(UPrimitiveComponent* meshComponent, int lod) {

	if (!IsValid(meshComponent)) return TArray<FColor>();


	TArray<FColor> vertexColors_Local;


	if (auto staticMeshComponent = Cast<UStaticMeshComponent>(meshComponent)) {

		if (lod < 0) return vertexColors_Local;

		vertexColors_Local = GetStaticMeshVertexColorsAtLOD(staticMeshComponent, lod);
	}

	else if (auto skeletalMeshComponent = Cast<USkeletalMeshComponent>(meshComponent)) {

		if (lod < 0) return vertexColors_Local;

		vertexColors_Local = GetSkeletalMeshVertexColorsAtLOD(skeletalMeshComponent, lod);
	}

#if ENGINE_MAJOR_VERSION == 5

	else if (auto dynamicMeshComponent = Cast<UDynamicMeshComponent>(meshComponent)) {

		vertexColors_Local = GetDynamicMeshVertexColors(dynamicMeshComponent);
	}

	else if (auto geometryCollectionComponent = Cast<UGeometryCollectionComponent>(meshComponent)) {


		vertexColors_Local = GetGeometryCollectionVertexColors(geometryCollectionComponent);
	}

#endif


	return vertexColors_Local;
}


//--------------------------------------------------------

// Get Skeletal Mesh Vertex Colors At LOD

TArray<FColor> VertexPaintFunctions::GetSkeletalMeshVertexColorsAtLOD(USkeletalMeshComponent* skeletalMeshComponent, int lod) {

	if (!IsValid(skeletalMeshComponent)) return TArray<FColor>();


	TArray<FColor> colorFromLOD_Local;

	if (skeletalMeshComponent->LODInfo.IsValidIndex(lod)) {

		// If been painted on before then can get the current Instance Color
		if (skeletalMeshComponent->LODInfo[lod].OverrideVertexColors) {

			skeletalMeshComponent->LODInfo[lod].OverrideVertexColors->GetVertexColors(colorFromLOD_Local);
		}
		else {

			if (skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData.IsValidIndex(lod))
				skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[lod].StaticVertexBuffers.ColorVertexBuffer.GetVertexColors(colorFromLOD_Local);
		}
	}

	else {

		if (skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData.IsValidIndex(lod))
			skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[lod].StaticVertexBuffers.ColorVertexBuffer.GetVertexColors(colorFromLOD_Local);
	}


	// In one instance when i tested on a side project with a purchased character, it got 0 in Num when first time painting at it, i.e. got vertex colors from SkeletalMeshRenderData. This only occured if the character hadn't gotten any paint on it and was imported with FColor(255,255,255,255) so it was an easy solution to just fill arrays to that color in this rare instance. So unlike the static mesh solution i couldn't initialize colorFromLOD_Local to be a length before running GetVertexColors because then i couldn't detect this rare case. 
	if (colorFromLOD_Local.Num() > 0) {

		// 
	}

	else {

		if (skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData.IsValidIndex(lod))
			colorFromLOD_Local.Init(FColor(255, 255, 255, 255), skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[lod].GetNumVertices());
	}

	return colorFromLOD_Local;
}


//--------------------------------------------------------

// Get Static Mesh Vertex Colors At LOD

TArray<FColor> VertexPaintFunctions::GetStaticMeshVertexColorsAtLOD(UStaticMeshComponent* staticMeshComponent, int lod) {

	if (!IsValid(staticMeshComponent)) return TArray<FColor>();
	if (!IsValid(staticMeshComponent->GetStaticMesh())) return TArray<FColor>();
	if (!staticMeshComponent->GetStaticMesh()->bAllowCPUAccess) return TArray<FColor>();
	if (!staticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources.IsValidIndex(lod)) return TArray<FColor>();


	TArray<FColor> colorFromLOD_Local;
	FColorVertexBuffer* colVertBufferAtLOD_Local = nullptr;
	int meshLODTotalAmountOfVerts_Local = staticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources[lod].VertexBuffers.PositionVertexBuffer.GetNumVertices();

	colorFromLOD_Local.SetNum(meshLODTotalAmountOfVerts_Local, true);

	// Depending if override vertex colors is valid, we get the Vertex Colors from it, i.e. the instanced colors
	if (staticMeshComponent->LODData.IsValidIndex(lod)) {

		if (staticMeshComponent->LODData[lod].OverrideVertexColors) {

			staticMeshComponent->LODData[lod].OverrideVertexColors->GetVertexColors(colorFromLOD_Local);
		}

		else {

			staticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources[lod].VertexBuffers.ColorVertexBuffer.GetVertexColors(colorFromLOD_Local);
		}
	}

	else {

		colVertBufferAtLOD_Local = &staticMeshComponent->GetStaticMesh()->GetRenderData()->LODResources[lod].VertexBuffers.ColorVertexBuffer;

		// If color buffer isn't initialized it means its default colors are White and it hasn't been painted either in editor or in runtime, if this is the case we init the array with white so even unstored, unpainted cpu meshes with all default white vertex colors can be painted and look as they should. 
		if (colVertBufferAtLOD_Local) {

			if (colVertBufferAtLOD_Local->IsInitialized()) {

				colVertBufferAtLOD_Local->GetVertexColors(colorFromLOD_Local);
			}
			else {

				colorFromLOD_Local.Init(FColor::White, meshLODTotalAmountOfVerts_Local);
			}
		}

		else {

			colorFromLOD_Local.Init(FColor::White, meshLODTotalAmountOfVerts_Local);
		}
	}

	return colorFromLOD_Local;
}


//--------------------------------------------------------

// Get Vertex Paint Task Queue

UVertexPaintDetectionTaskQueue* VertexPaintFunctions::GetVertexPaintTaskQueue(const UObject* WorldContextObject) {

	if (!WorldContextObject) return nullptr;

	return GetVertexPaintGameInstanceSubsystem(WorldContextObject)->GetVertexPaintTaskQueue();
}

#if ENGINE_MAJOR_VERSION == 5


//--------------------------------------------------------

// Get Dynamic Mesh Vertex Colors

TArray<FColor> VertexPaintFunctions::GetDynamicMeshVertexColors(UDynamicMeshComponent* dynamicMeshComponent) {

	TArray<FColor> colorFromLOD_Local;

	if (IsValid(dynamicMeshComponent)) {

		if (dynamicMeshComponent->GetDynamicMesh()) {

			UE::Geometry::FDynamicMesh3* dynamicMesh3 = nullptr;
			dynamicMesh3 = &dynamicMeshComponent->GetDynamicMesh()->GetMeshRef();

			if (dynamicMesh3) {

				UE::Geometry::FVertexInfo vertexInfoTemp;
				colorFromLOD_Local.SetNumUninitialized(dynamicMesh3->MaxVertexID(), false);

				for (int i = 0; i < dynamicMesh3->MaxVertexID(); i++) {

					vertexInfoTemp = UE::Geometry::FVertexInfo();
					vertexInfoTemp = dynamicMesh3->GetVertexInfo(i);

					if (vertexInfoTemp.bHaveC)
						colorFromLOD_Local[i] = (FColor(vertexInfoTemp.Color.X, vertexInfoTemp.Color.Y, vertexInfoTemp.Color.Z, 0));
				}
			}
		}
	}

	return colorFromLOD_Local;
}


//--------------------------------------------------------

// Get Geometry Collection Vertex Colors

TArray<FColor> VertexPaintFunctions::GetGeometryCollectionVertexColors(UGeometryCollectionComponent* geometryCollectionComponent) {

	TArray<FColor> colorFromLOD_Local;


	// Geometry Collection Only available from 5.3 and up

#if ENGINE_MINOR_VERSION >= 3

	if (IsValid(geometryCollectionComponent)) {

		UGeometryCollection* geometryCollection = const_cast<UGeometryCollection*>(geometryCollectionComponent->GetRestCollection());

		if (geometryCollection) {

			TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> geometryCollectionData = geometryCollection->GetGeometryCollection();

			if (geometryCollectionData.Get()) {

				for (auto colorsTemp : geometryCollectionData->Color)
					colorFromLOD_Local.Add(colorsTemp.ToFColor(false));
			}
		}
	}

#endif

	return colorFromLOD_Local;
}
#endif


//-------------------------------------------------------

// Collision Channel to Object Type

EObjectTypeQuery VertexPaintFunctions::CollisionChannelToObjectType(ECollisionChannel channel) {

	// Has this here since i don't want to include UnrealTypes in.h
	return UEngineTypes::ConvertToObjectType(channel);
}


//-------------------------------------------------------

// Object Type to Collision Channel

ECollisionChannel VertexPaintFunctions::ObjectTypeToCollisionChannel(EObjectTypeQuery object) {

	// Has this here since i don't want to include UnrealTypes in.h
	return UEngineTypes::ConvertToCollisionChannel(object);
}


//-------------------------------------------------------

// Is In Editor

bool VertexPaintFunctions::IsPlayInEditor(const UObject* WorldContextObject) {

	if (!IsValid(WorldContextObject)) return false;
	if (!IsValid(WorldContextObject->GetWorld())) return false;
	if (!IsWorldValid(WorldContextObject->GetWorld())) return false;

	return WorldContextObject->GetWorld()->IsPlayInEditor();
}


//-------------------------------------------------------

// Does Physics Surface Belong To Parent Surface

bool VertexPaintFunctions::DoesPhysicsSurfaceBelongToPhysicsSurfaceFamily(const UObject* WorldContextObject, TEnumAsByte<EPhysicalSurface> physicsSurface, TEnumAsByte<EPhysicalSurface> parentOfPhysicsSurfaceFamily) {

	if (physicsSurface == EPhysicalSurface::SurfaceType_Default) return false;
	if (parentOfPhysicsSurfaceFamily == EPhysicalSurface::SurfaceType_Default) return false;

	if (auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject)) {

		if (!materialDataAsset->GetPhysicsSurfaceFamilies().Contains(parentOfPhysicsSurfaceFamily)) return false;

		// If its the parent surface itself. 
		if (physicsSurface == parentOfPhysicsSurfaceFamily) return true;

		if (materialDataAsset->GetPhysicsSurfaceFamilies().FindRef(parentOfPhysicsSurfaceFamily).childSurfaces.Contains(physicsSurface)) return true;
	}

	return false;
}


//-------------------------------------------------------

// Get Vertex Paint Material Interface

TMap<TSoftObjectPtr<UMaterialInterface>, FVertexPaintMaterialDataAssetStruct> VertexPaintFunctions::GetVertexPaintMaterialInterface_Wrapper(const UObject* WorldContextObject) {

	if (auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject))
		return materialDataAsset->GetVertexPaintMaterialInterface();

	return TMap<TSoftObjectPtr<UMaterialInterface>, FVertexPaintMaterialDataAssetStruct>();
}


//-------------------------------------------------------

// Is Material Added To Paint On Material Data Asset

bool VertexPaintFunctions::IsMaterialAddedToPaintOnMaterialDataAsset_Wrapper(const UObject* WorldContextObject, TSoftObjectPtr<UMaterialInterface> material) {

	if (auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject))
		return materialDataAsset->IsMaterialAddedToPaintOnMaterialDataAsset(material);

	return false;
}


//-------------------------------------------------------

// Get Parents Of Physics Surface

TArray<TEnumAsByte<EPhysicalSurface>> VertexPaintFunctions::GetParentsOfPhysicsSurface_Wrapper(const UObject* WorldContextObject, TEnumAsByte<EPhysicalSurface> physicalSurface) {

	if (auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject))
		return materialDataAsset->GetParentsOfPhysicsSurface(physicalSurface);

	return TArray<TEnumAsByte<EPhysicalSurface>>();
}


//-------------------------------------------------------

// Get Physics Surface Families

TMap<TEnumAsByte<EPhysicalSurface>, FVertexPaintParentPhysicsSurfaceStruct> VertexPaintFunctions::GetPhysicsSurfaceFamilies_Wrapper(const UObject* WorldContextObject) {

	if (auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject))
		return materialDataAsset->GetPhysicsSurfaceFamilies();

	return TMap<TEnumAsByte<EPhysicalSurface>, FVertexPaintParentPhysicsSurfaceStruct>();
}


//-------------------------------------------------------

// Get Physics Surfaces Registered To Material

TArray<TEnumAsByte<EPhysicalSurface>> VertexPaintFunctions::GetPhysicsSurfacesRegisteredToMaterial(const UObject* WorldContextObject, UMaterialInterface* material) {

	if (!IsValid(material)) return TArray<TEnumAsByte<EPhysicalSurface>>();

	if (auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject)) {


		UMaterialInterface* materialToGetPhysicsSurfacesTemp = materialDataAsset->GetRegisteredMaterialInstanceOrParentMaterial(material);

		if (!materialDataAsset->GetVertexPaintMaterialInterface().Contains(materialToGetPhysicsSurfacesTemp)) return TArray<TEnumAsByte<EPhysicalSurface>>();

		TArray<TEnumAsByte<EPhysicalSurface>> physicsSurfacesRegisteredToMaterialTemp;

		// Fills Elements for each channel, even if it may have Default so it will be easier to work with 
		physicsSurfacesRegisteredToMaterialTemp.Add(materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToGetPhysicsSurfacesTemp).paintedAtRed);
		physicsSurfacesRegisteredToMaterialTemp.Add(materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToGetPhysicsSurfacesTemp).paintedAtGreen);
		physicsSurfacesRegisteredToMaterialTemp.Add(materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToGetPhysicsSurfacesTemp).paintedAtBlue);
		physicsSurfacesRegisteredToMaterialTemp.Add(materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToGetPhysicsSurfacesTemp).paintedAtAlpha);

		return physicsSurfacesRegisteredToMaterialTemp;
	}

	return TArray<TEnumAsByte<EPhysicalSurface>>();
}


//-------------------------------------------------------

// Get Colors To Apply Based Off Detected Physics Material

void VertexPaintFunctions::GetColorsToApplyFromPhysicsSurface_Wrapper(const UObject* WorldContextObject, UMaterialInterface* materialToApplyColorsTo, const TEnumAsByte<EPhysicalSurface>& physicalSurface, float& redAmountToApply, bool& redAmountSuccessfullyGot, float& greenAmountToApply, bool& greenAmountSuccessfullyGot, float& blueAmountToApply, bool& blueAmountSuccessfullyGot, float& alphaAmountToApply, bool& alphaAmountSuccessfullyGot, bool& successfullyGotColorsToApplyOnAChannel, float amountToReturnOnChannelsWithPhysicsSurface, float amountToReturnOnChannelsWithoutThePhysicsSurface, bool applyOnChannelsWithSamePhysicsParents, bool applyOnChannelsThatsChildOfPhysicsSurface, bool applyOnChannelsThatResultsInBlendableSurfaces) {

	successfullyGotColorsToApplyOnAChannel = false;

	redAmountToApply = 0;
	redAmountSuccessfullyGot = false;

	greenAmountToApply = 0;
	greenAmountSuccessfullyGot = false;

	blueAmountToApply = 0;
	blueAmountSuccessfullyGot = false;

	alphaAmountToApply = 0;
	alphaAmountSuccessfullyGot = false;


	// if (amountToReturnOnChannelsWithPhysicsSurface == 0) return; // We DON'T want to return if 0, since if we're painting with Set instead of Adding, then 0 may be what we want. 
	if (physicalSurface == EPhysicalSurface::SurfaceType_Default) return;

	auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject);
	if (!materialDataAsset) return;

	materialToApplyColorsTo = materialDataAsset->GetRegisteredMaterialInstanceOrParentMaterial(materialToApplyColorsTo);
	if (!IsValid(materialToApplyColorsTo)) return;



	TEnumAsByte<EPhysicalSurface> physicsSurfacePaintedAtRed = materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToApplyColorsTo).paintedAtRed;
	TEnumAsByte<EPhysicalSurface> physicsSurfacePaintedAtGreen = materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToApplyColorsTo).paintedAtGreen;
	TEnumAsByte<EPhysicalSurface> physicsSurfacePaintedAtBlue = materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToApplyColorsTo).paintedAtBlue;
	TEnumAsByte<EPhysicalSurface> physicsSurfacePaintedAtAlpha = materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToApplyColorsTo).paintedAtAlpha;


	// If Exactly what we're trying to paint is on the channel
	if (physicalSurface == physicsSurfacePaintedAtRed)
		redAmountSuccessfullyGot = true;

	if (physicalSurface == physicsSurfacePaintedAtGreen)
		greenAmountSuccessfullyGot = true;

	if (physicalSurface == physicsSurfacePaintedAtBlue)
		blueAmountSuccessfullyGot = true;

	if (physicalSurface == physicsSurfacePaintedAtAlpha)
		alphaAmountSuccessfullyGot = true;


	TArray<TEnumAsByte<EPhysicalSurface>> parentPhysicsSurfaceTemp = materialDataAsset->GetParentsOfPhysicsSurface(physicalSurface);

	// If we want to Apply on the channel if it has a Parent of what's on the Channel. For instance Cobble-Sand didn't exist on any of the Channels, but Sand which is a Parent does exist, then we want to apply. Useful if for instance Characters that has fundemental Parent Surfaces like Sand, Mud etc. is walking over different types of Sandy/Muddy surfaces and we want them to rub off on the correct channel on the character. 
	if (applyOnChannelsWithSamePhysicsParents) {

		if (!redAmountSuccessfullyGot && parentPhysicsSurfaceTemp.Contains(physicsSurfacePaintedAtRed))
			redAmountSuccessfullyGot = true;

		if (!greenAmountSuccessfullyGot && parentPhysicsSurfaceTemp.Contains(physicsSurfacePaintedAtGreen))
			greenAmountSuccessfullyGot = true;

		if (!blueAmountSuccessfullyGot && parentPhysicsSurfaceTemp.Contains(physicsSurfacePaintedAtBlue))
			blueAmountSuccessfullyGot = true;

		if (!alphaAmountSuccessfullyGot && parentPhysicsSurfaceTemp.Contains(physicsSurfacePaintedAtAlpha))
			alphaAmountSuccessfullyGot = true;
	}


	FVertexPaintParentPhysicsSurfaceStruct physicsSurfaceFamilyTemp;

	// Checks if physics surface we're trying to apply is a parent, and if what's on each of the vertex color channels is a child of that parent. Then we can apply color on that channel as well. This can be useful if for instance you have a Wheel with Parent Surface Sand on it, that is driving over a Material that doesn't have Sand registered, but it has Cobble-Sand which is a child of it. Then the sandy Wheel can Rub off on the correct channel and spread Sand onto the Cobble-Sand. 
	if (applyOnChannelsThatsChildOfPhysicsSurface && materialDataAsset->GetPhysicsSurfaceFamilies().Contains(physicalSurface)) {

		physicsSurfaceFamilyTemp = materialDataAsset->GetPhysicsSurfaceFamilies().FindRef(physicalSurface);

		if (physicsSurfaceFamilyTemp.childSurfaces.Num() > 0) {

			if (!redAmountSuccessfullyGot) {

				if (physicsSurfaceFamilyTemp.childSurfaces.Contains(physicsSurfacePaintedAtRed))
					redAmountSuccessfullyGot = true;
			}

			if (!greenAmountSuccessfullyGot) {

				if (physicsSurfaceFamilyTemp.childSurfaces.Contains(physicsSurfacePaintedAtGreen))
					greenAmountSuccessfullyGot = true;
			}

			if (!blueAmountSuccessfullyGot) {

				if (physicsSurfaceFamilyTemp.childSurfaces.Contains(physicsSurfacePaintedAtBlue))
					blueAmountSuccessfullyGot = true;
			}

			if (!alphaAmountSuccessfullyGot) {

				if (physicsSurfaceFamilyTemp.childSurfaces.Contains(physicsSurfacePaintedAtAlpha))
					alphaAmountSuccessfullyGot = true;
			}
		}
	}



	// Checks Physics Surfaces that it can Blend into as well, if we're trying to apply a blended surface or if we should apply it on parents or childs of it. In the Example Project for instance we have a Cobble Material with Cobble-Sand on Red Channel, and Cobble-Puddle on Blue, which can blend into Cobble-Mud, which is a child of Mud. So if for instance a wheel that has Mud that is driving over the Cobble Material, we can with this get Cobble-Mud if set to applyOnChannelsThatsChildOfPhysicsSurface, and that it's a child of Mud, which means the Wheel with Mud can paint off itself on the channels that formed Cobble-Mud. Same way other way around if applyOnChannelsWithSamePhysicsParents is true, where a clean wheel can get painted with Mud by Cobble-Mud. 
	if (applyOnChannelsThatResultsInBlendableSurfaces) {

		// Gets Physics Surface Blend Settings on the Material we're Applying Colors on, for instance the Cobble Material from the Example Project has some registered 
		for (auto& blendSettingTemp : materialDataAsset->GetVertexPaintMaterialInterface().FindRef(materialToApplyColorsTo).physicsSurfaceBlendingSettings) {

			// If we're trying to apply a Blendable Surface, for instance Cobble-Mud, Or we've set to affect childs of a parent, for instance Mud, and we find the Blendable Cobble-Mud as a child
			if (blendSettingTemp.Key == physicalSurface || (applyOnChannelsThatsChildOfPhysicsSurface && physicsSurfaceFamilyTemp.childSurfaces.Contains(blendSettingTemp.Key)) || (applyOnChannelsWithSamePhysicsParents && parentPhysicsSurfaceTemp.Contains(blendSettingTemp.Key))) {

				TArray<TEnumAsByte<EPhysicalSurface>> blendableParentsPhysicsSurfaceTemp = materialDataAsset->GetParentsOfPhysicsSurface(blendSettingTemp.Key);


				// Now we know that the Blended Surface checks out, and we just need to get which vertex color channels that was the result of that blend, so we can set those channels to return the correct amount. To do this we loop through the physics surfaces that resultet in the blend, and then runs GetVertexColorChannelsPhysicsSurfaceIsRegisteredTo on that physics surface
				for (auto physicsSurfacesThatBlendedIntoEachotherTemp : blendSettingTemp.Value.physicsSurfacesThatCanBlend) {

					bool successfullyGotChannelPhysicsSurfaceIsRegisteredToLocal = false;
					auto channelPhysicsSurfaceIsRegisteredTo_Local = GetVertexColorChannelsPhysicsSurfaceIsRegisteredTo(WorldContextObject, materialToApplyColorsTo, physicsSurfacesThatBlendedIntoEachotherTemp, successfullyGotChannelPhysicsSurfaceIsRegisteredToLocal);

					if (successfullyGotChannelPhysicsSurfaceIsRegisteredToLocal) {

						for (auto vertexColorChannel : channelPhysicsSurfaceIsRegisteredTo_Local) {

							switch (vertexColorChannel) {

							case Enum_SurfaceAtChannel::Default:
								break;

							case Enum_SurfaceAtChannel::RedChannel:

								redAmountSuccessfullyGot = true;
								break;

							case Enum_SurfaceAtChannel::GreenChannel:

								greenAmountSuccessfullyGot = true;
								break;

							case Enum_SurfaceAtChannel::BlueChannel:

								blueAmountSuccessfullyGot = true;
								break;

							case Enum_SurfaceAtChannel::AlphaChannel:

								alphaAmountSuccessfullyGot = true;
								break;

							default:
								break;
							}
						}
					}
				}
			}
		}
	}


	if (redAmountSuccessfullyGot)
		redAmountToApply = amountToReturnOnChannelsWithPhysicsSurface;
	else
		redAmountToApply = amountToReturnOnChannelsWithoutThePhysicsSurface;


	if (greenAmountSuccessfullyGot)
		greenAmountToApply = amountToReturnOnChannelsWithPhysicsSurface;
	else
		greenAmountToApply = amountToReturnOnChannelsWithoutThePhysicsSurface;


	if (blueAmountSuccessfullyGot)
		blueAmountToApply = amountToReturnOnChannelsWithPhysicsSurface;
	else
		blueAmountToApply = amountToReturnOnChannelsWithoutThePhysicsSurface;


	if (alphaAmountSuccessfullyGot)
		alphaAmountToApply = amountToReturnOnChannelsWithPhysicsSurface;
	else
		alphaAmountToApply = amountToReturnOnChannelsWithoutThePhysicsSurface;


	// If managed to get color to apply on any channel at all. 
	if (redAmountSuccessfullyGot || greenAmountSuccessfullyGot || blueAmountSuccessfullyGot || alphaAmountSuccessfullyGot) {

		successfullyGotColorsToApplyOnAChannel = true;
	}

	else {

		redAmountToApply = 0;
		greenAmountToApply = 0;
		blueAmountToApply = 0;
		alphaAmountToApply = 0;
	}
}


//-------------------------------------------------------

// Get The Most Dominant Physics Surface

bool VertexPaintFunctions::GetTheMostDominantPhysicsSurface_Wrapper(const UObject* WorldContextObject, UMaterialInterface* optionalMaterialPhysicsSurfaceWasDetectedOn, TArray<TEnumAsByte<EPhysicalSurface>> physicsSurfaces, TArray<float> physicsSurfaceValues, TEnumAsByte<EPhysicalSurface>& mostDominantPhysicsSurfaceFromArray, float& mostDominantPhysicsSurfaceColorValue) {

	mostDominantPhysicsSurfaceFromArray = EPhysicalSurface::SurfaceType_Default;
	mostDominantPhysicsSurfaceColorValue = 0;

	if (physicsSurfaces.Num() <= 0) return false;
	if (physicsSurfaceValues.Num() <= 0) return false;
	if (physicsSurfaces.Num() != physicsSurfaceValues.Num()) return false;

	float strongestSurfaceValue_Local = 0;
	TEnumAsByte<EPhysicalSurface> strongestSurface_Local = EPhysicalSurface::SurfaceType_Default;
	TArray<TEnumAsByte<EPhysicalSurface>> blendedSurfaceResults_Local;
	TArray<float> blendedSurfaceValueResults_Local;


	// First just gets the surface with the strongest value
	for (int i = 0; i < physicsSurfaces.Num(); i++) {

		// Has to have something. So if you send in an array where everything is 0 then you shouldn't be able to get a dominant surface
		if (physicsSurfaceValues[i] > 0) {

			if (physicsSurfaceValues[i] >= strongestSurfaceValue_Local) {

				strongestSurface_Local = physicsSurfaces[i];
				strongestSurfaceValue_Local = physicsSurfaceValues[i];
			}
		}
	}

	auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject);

	// If material is registered then checks if any of the surfaces can blend
	if (materialDataAsset) {


		TArray<FVertexPaintPhysicsSurfaceBlendingSettings> surfaceBlendSettings_Local;


		if (!materialDataAsset->GetVertexPaintMaterialInterface().Contains(optionalMaterialPhysicsSurfaceWasDetectedOn)) {

			// If not registered, then if it's an instance, then replaces material with the parent and checks that. Makes it possible so you don't have to register every single instance but can if you wish only register the parent
			if (auto materialInstanceTemp = Cast<UMaterialInstance>(optionalMaterialPhysicsSurfaceWasDetectedOn)) {

				optionalMaterialPhysicsSurfaceWasDetectedOn = materialInstanceTemp->Parent;
			}
		}


		if (materialDataAsset->GetVertexPaintMaterialInterface().Contains(optionalMaterialPhysicsSurfaceWasDetectedOn)) {

			materialDataAsset->GetVertexPaintMaterialInterface().FindRef(optionalMaterialPhysicsSurfaceWasDetectedOn).physicsSurfaceBlendingSettings.GenerateValueArray(surfaceBlendSettings_Local);


			bool blendedSurfaces_ContainsAll_Local = true;
			bool blendedSurfaces_AllHaveMinAmount_Local = true;
			float blendedSurfaces_TotalAmount_Local = 0;


			// Then checks if any of the surface we got as a parameter can blendand if their value combined allows them to blendand is then the strongest surface
			if (surfaceBlendSettings_Local.Num() > 0) {

				for (auto blendSettingTemp : surfaceBlendSettings_Local) {

					blendedSurfaces_ContainsAll_Local = true;

					// If the phys surface array sent in even has all necessary surfaces for this blend setting
					for (auto physSurfaceThatBlendTemp : blendSettingTemp.physicsSurfacesThatCanBlend) {

						if (!physicsSurfaces.Contains(physSurfaceThatBlendTemp)) {

							blendedSurfaces_ContainsAll_Local = false;
							break;
						}
					}

					if (!blendedSurfaces_ContainsAll_Local) continue;


					blendedSurfaces_AllHaveMinAmount_Local = true;
					blendedSurfaces_TotalAmount_Local = 0;

					// If we know we have all phys surfaces requires, then checks if each has min required color amount that they require to blend
					for (auto physSurfaceThatBlendTemp : blendSettingTemp.physicsSurfacesThatCanBlend) {

						if (physicsSurfaceValues[physicsSurfaces.Find(physSurfaceThatBlendTemp)] >= blendSettingTemp.minAmountOnEachSurfaceToBeAbleToBlend) {

							blendedSurfaces_TotalAmount_Local += physicsSurfaceValues[physicsSurfaces.Find(physSurfaceThatBlendTemp)];
						}
						else {

							blendedSurfaces_AllHaveMinAmount_Local = false;
							break;
						}
					}

					if (!blendedSurfaces_AllHaveMinAmount_Local) continue;


					blendedSurfaceResults_Local.Add(blendSettingTemp.physicsSurfaceToResultIn);
					blendedSurfaceValueResults_Local.Add(blendedSurfaces_TotalAmount_Local);
				}
			}
		}
	}

	// If got any blendes surfaces then checks if they're stronger than the strongest surface we got earlier when we checked them invidiually and updates it. If there are several blendes surfaces, the one that combines has the strongest value will be considered the strongest surface
	if (blendedSurfaceValueResults_Local.Num() > 0) {

		for (int i = 0; i < blendedSurfaceValueResults_Local.Num(); i++) {

			if (blendedSurfaceValueResults_Local[i] > strongestSurfaceValue_Local) {


				strongestSurfaceValue_Local = blendedSurfaceValueResults_Local[i];
				strongestSurface_Local = blendedSurfaceResults_Local[i];
			}
		}
	}

	// Only returns true if we actually got a surface, if they where all 0 so strongest surface is the default 0 then we don't want to return anything surface
	if (strongestSurface_Local != EPhysicalSurface::SurfaceType_Default && strongestSurfaceValue_Local > 0) {

		mostDominantPhysicsSurfaceFromArray = strongestSurface_Local;
		mostDominantPhysicsSurfaceColorValue = strongestSurfaceValue_Local;

		return true;
	}

	return false;
}


//-------------------------------------------------------

// Get Vertex Color Channels Physics Surface Is Registered To Wrapper

TArray<Enum_SurfaceAtChannel> VertexPaintFunctions::GetAllVertexColorChannelsPhysicsSurfaceIsRegisteredTo_Wrapper(const UObject* WorldContextObject, UMaterialInterface* material, TEnumAsByte<EPhysicalSurface> physicsSurface, bool& successfull) {

	successfull = false;
	TArray< Enum_SurfaceAtChannel> surfaceAtChannels; // Array in case it's a blendable where there are several channels that make up the physics surface

	if (!IsValid(material)) return surfaceAtChannels;

	auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject);
	if (!materialDataAsset) return surfaceAtChannels;


	if (!materialDataAsset->GetVertexPaintMaterialInterface().Contains(material)) {

		// If not registered, then if it's an instance, then replaces material with the parent and checks that. Makes it possible so you don't have to register every single instance but can if you wish only register the parent
		if (auto materialInstanceTemp = Cast<UMaterialInstance>(material)) {

			material = materialInstanceTemp->Parent;

			if (!materialDataAsset->GetVertexPaintMaterialInterface().Contains(material))
				return surfaceAtChannels;
		}
		else {

			return surfaceAtChannels;
		}
	}


	auto materialDataAssetTemp = materialDataAsset->GetVertexPaintMaterialInterface().FindRef(material);

	// Gets if physics surface is registered to R, G, B or A for this Material, if so then returns
	surfaceAtChannels = GetVertexColorChannelsPhysicsSurfaceIsRegisteredTo(WorldContextObject, material, physicsSurface, successfull);

	if (successfull) {

		return surfaceAtChannels;
	}

	// If couldn't find any, then checks if there are several blendables that make up this surface, and get the surface channels for them. 
	for (auto& blendSettingTemp : materialDataAssetTemp.physicsSurfaceBlendingSettings) {

		if (blendSettingTemp.Key == physicsSurface) {

			for (auto blendedPhysSurfacesThatMakeUpThePhysicsSurface : blendSettingTemp.Value.physicsSurfacesThatCanBlend) {

				TArray< Enum_SurfaceAtChannel> blendableChannelsThatMakeUpPhysicsSurfaceTemp = GetVertexColorChannelsPhysicsSurfaceIsRegisteredTo(WorldContextObject, material, blendedPhysSurfacesThatMakeUpThePhysicsSurface, successfull);

				if (successfull)
					surfaceAtChannels.Append(blendableChannelsThatMakeUpPhysicsSurfaceTemp);
			}

			if (successfull)
				return surfaceAtChannels;
		}
	}

	return surfaceAtChannels;
}


//-------------------------------------------------------

// Get Vertex Color Channels Physics Surface Is Registered To - This just checks the RGBA channels and not Blendables like the one above

TArray<Enum_SurfaceAtChannel> VertexPaintFunctions::GetVertexColorChannelsPhysicsSurfaceIsRegisteredTo(const UObject* WorldContextObject, UMaterialInterface* material, TEnumAsByte<EPhysicalSurface> physicsSurface, bool& successfull) {

	successfull = false;

	if (!IsValid(material)) return TArray<Enum_SurfaceAtChannel>();

	auto materialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(WorldContextObject);
	if (!materialDataAsset) return TArray<Enum_SurfaceAtChannel>();

	if (!materialDataAsset->GetVertexPaintMaterialInterface().Contains(material)) {

		// If not registered, then if it's an instance, then replaces material with the parent and checks that. Makes it possible so you don't have to register every single instance but can if you wish only register the parent
		if (auto materialInstanceTemp = Cast<UMaterialInstance>(material)) {

			material = materialInstanceTemp->Parent;

			if (!materialDataAsset->GetVertexPaintMaterialInterface().Contains(material))
				return TArray<Enum_SurfaceAtChannel>();
		}
		else {

			return TArray<Enum_SurfaceAtChannel>();
		}
	}

	auto materialDataAssetTemp = materialDataAsset->GetVertexPaintMaterialInterface().FindRef(material);

	TArray<Enum_SurfaceAtChannel> atSurfaceChannels_Local;


	if (materialDataAssetTemp.atDefault == physicsSurface) {

		successfull = true;
		atSurfaceChannels_Local.Add(Enum_SurfaceAtChannel::Default);
	}

	if (materialDataAssetTemp.paintedAtRed == physicsSurface) {

		successfull = true;
		atSurfaceChannels_Local.Add(Enum_SurfaceAtChannel::RedChannel);
	}

	if (materialDataAssetTemp.paintedAtGreen == physicsSurface) {

		successfull = true;
		atSurfaceChannels_Local.Add(Enum_SurfaceAtChannel::GreenChannel);
	}

	if (materialDataAssetTemp.paintedAtBlue == physicsSurface) {

		successfull = true;
		atSurfaceChannels_Local.Add(Enum_SurfaceAtChannel::BlueChannel);
	}

	if (materialDataAssetTemp.paintedAtAlpha == physicsSurface) {

		successfull = true;
		atSurfaceChannels_Local.Add(Enum_SurfaceAtChannel::AlphaChannel);
	}

	return atSurfaceChannels_Local;
}


//--------------------------------------------------------

// Get Clothing Assets

TArray<UClothingAssetBase*> VertexPaintFunctions::GetClothAssets(USkeletalMesh* skeletalMesh) {

	if (!IsValid(skeletalMesh)) return TArray<UClothingAssetBase*>();

	return skeletalMesh->GetMeshClothingAssets();
}


//-------------------------------------------------------

// Set Cloth Physics

void VertexPaintFunctions::SetChaosClothPhysics(USkeletalMeshComponent* skeletalMeshComponent, UClothingAssetBase* clothingAsset, const FVertexDetectChaosClothPhysicsSettings& clothPhysicsSettings) {

#if ENGINE_MAJOR_VERSION == 5

	if (!IsValid(skeletalMeshComponent) || !IsValid(clothingAsset)) return;


	auto clothingSimulationInteractorTemp = skeletalMeshComponent->GetClothingSimulationInteractor();

	if (auto chaosClothingSimilationInteractorTemp = Cast<UChaosClothingSimulationInteractor>(clothingSimulationInteractorTemp)) {

		if (auto clothingInteractorTemp = chaosClothingSimilationInteractorTemp->GetClothingInteractor(clothingAsset->GetName())) {

			if (auto chaosClothingInteractorTemp = Cast<UChaosClothingInteractor>(clothingInteractorTemp)) {


				if (clothPhysicsSettings.SetDamping)
					chaosClothingInteractorTemp->SetDamping(clothPhysicsSettings.clothDampingSettings.SetDamping_dampingCoefficient);

				if (clothPhysicsSettings.SetGravity)
					chaosClothingInteractorTemp->SetGravity(clothPhysicsSettings.clothGravitySettings.SetGravity_gravityScale, clothPhysicsSettings.clothGravitySettings.SetGravity_overrideGravity, clothPhysicsSettings.clothGravitySettings.SetGravity_gravityOverride);

				if (clothPhysicsSettings.SetWind)
					chaosClothingInteractorTemp->SetWind(clothPhysicsSettings.clothWindSettings.SetWind_drag, clothPhysicsSettings.clothWindSettings.SetWind_lift, clothPhysicsSettings.clothWindSettings.SetWind_airDensity, clothPhysicsSettings.clothWindSettings.SetWind_windVelocity);

				if (clothPhysicsSettings.SetAnimDrive)
					chaosClothingInteractorTemp->SetAnimDrive(clothPhysicsSettings.clothAnimDriveSettings.SetAnimDrive_Stiffness, clothPhysicsSettings.clothAnimDriveSettings.SetAnimDrive_Damping);

				if (clothPhysicsSettings.SetCollision)
					chaosClothingInteractorTemp->SetCollision(clothPhysicsSettings.clothCollisionSettings.SetCollision_CollisionThickness, clothPhysicsSettings.clothCollisionSettings.SetCollision_FrictionCoefficient, clothPhysicsSettings.clothCollisionSettings.SetCollision_UseCCD, clothPhysicsSettings.clothCollisionSettings.SetCollision_SelfCollisionThickness);

				if (clothPhysicsSettings.SetLongRangeAttachment)
					chaosClothingInteractorTemp->SetLongRangeAttachment(clothPhysicsSettings.clothLongRangeAttachmentSettings.LongRangeAttachment_TetherThickness, clothPhysicsSettings.clothLongRangeAttachmentSettings.LongRangeAttachment_TetherScale);

				if (clothPhysicsSettings.SetMaterial)
					chaosClothingInteractorTemp->SetMaterial(clothPhysicsSettings.clothMaterialSettings.Material_EdgeStiffness, clothPhysicsSettings.clothMaterialSettings.Material_BendingStiffness, clothPhysicsSettings.clothMaterialSettings.Material_AreaStiffness);

				if (clothPhysicsSettings.SetPhysicsVelocityScale)
					chaosClothingInteractorTemp->SetVelocityScale(clothPhysicsSettings.clothPhysicsVelocityScaleSettings.PhysicsVelocityScale_LinearVelocityScale, clothPhysicsSettings.clothPhysicsVelocityScaleSettings.PhysicVelocityScale_AngularVelocityScale, clothPhysicsSettings.clothPhysicsVelocityScaleSettings.PhysicsVelocityScale_FictitiousAngularVelocityScale);

#if ENGINE_MINOR_VERSION >= 1

				if (clothPhysicsSettings.SetAirPressure) {
					chaosClothingInteractorTemp->SetPressure(clothPhysicsSettings.clothPhysicssAirPressureSettings.SetPressure_Pressure);
				}
#endif
			}
		}
	}


#endif
}


//-------------------------------------------------------

// Updated Chaos Cloth Physics With Existing Colors

void VertexPaintFunctions::UpdateChaosClothPhysicsWithExistingColors(USkeletalMeshComponent* skeletalMeshComponent) {

#if ENGINE_MAJOR_VERSION == 5

	if (!IsValid(skeletalMeshComponent)) return;

	UpdateChaosClothPhysics(skeletalMeshComponent->GetOwner(), skeletalMeshComponent, false, FLinearColor::White);

#endif
}

#if ENGINE_MAJOR_VERSION == 5

//-------------------------------------------------------

// Update Chaos Cloth Physics

void VertexPaintFunctions::UpdateChaosClothPhysics(AActor* actor, USkeletalMeshComponent* skeletalMeshComponent, bool useGivenColorAsAvarageColor, FLinearColor avarageColor) {

	if (!IsValid(skeletalMeshComponent) || !IsValid(actor)) return;
	if (!IsWorldValid(skeletalMeshComponent->GetWorld())) return;
	if (!IsInGameThread()) return;


	const FSkeletalMeshLODRenderData& skelMeshRenderDataTemp = skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[skeletalMeshComponent->GetPredictedLODLevel()];


	if (skelMeshRenderDataTemp.HasClothData()) {

		TMap<UClothingAssetBase*, FVertexDetectClothSettingsStruct> clothsAndTheirPhysicsSettings_Local;

		if (UKismetSystemLibrary::DoesImplementInterface(actor, UVertexPaintDetectionInterface::StaticClass()))
			clothsAndTheirPhysicsSettings_Local = IVertexPaintDetectionInterface::Execute_GetSkeletalMeshClothPhysicsSettings(actor, skeletalMeshComponent);


		if (clothsAndTheirPhysicsSettings_Local.Num() > 0) {

			USkeletalMesh* skelMeshTemp = nullptr;

#if ENGINE_MAJOR_VERSION == 4

			skelMeshTemp = skeletalMeshComponent->SkeletalMesh;

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

			skelMeshTemp = skeletalMeshComponent->SkeletalMesh.Get();

#else

			skelMeshTemp = skeletalMeshComponent->GetSkeletalMeshAsset();

#endif

#endif


			// Loops through Cloths
			for (int i = 0; i < skelMeshTemp->GetMeshClothingAssets().Num(); i++) {

				// Loops through Render Sections on current LOD
				for (int j = 0; j < skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[skeletalMeshComponent->GetPredictedLODLevel()].RenderSections.Num(); j++) {

					// When on the same section as the Cloth
					if (i == skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[skeletalMeshComponent->GetPredictedLODLevel()].RenderSections[j].CorrespondClothAssetIndex) {

						// Gets start and end vertex, which could be for instance 2300-2600 or something. So we get vertex colors below for just these verts
						int sectionStartVertexIndex = skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[skeletalMeshComponent->GetPredictedLODLevel()].RenderSections[j].BaseVertexIndex;

						int sectionTotalAmountOfVertices = sectionStartVertexIndex + skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[skeletalMeshComponent->GetPredictedLODLevel()].RenderSections[j].GetNumVertices();


						TArray<FColor> clothColorsTemp;

						// If Setting the entire mesh to be a specific color, then we already know the avarage color and doesn't have to run loops
						if (!useGivenColorAsAvarageColor) {

							FColor vertexColorTemp;
							for (int32 k = sectionStartVertexIndex; k < sectionTotalAmountOfVertices; k++) {


								// If been painted on before then can get the current Instance Color
								if (skeletalMeshComponent->LODInfo[skeletalMeshComponent->GetPredictedLODLevel()].OverrideVertexColors)
									vertexColorTemp = skeletalMeshComponent->LODInfo[skeletalMeshComponent->GetPredictedLODLevel()].OverrideVertexColors->VertexColor(k);

								// If haven't been painted on before then we get the Default Color
								else
									vertexColorTemp = skeletalMeshComponent->GetSkeletalMeshRenderData()->LODRenderData[skeletalMeshComponent->GetPredictedLODLevel()].StaticVertexBuffers.ColorVertexBuffer.VertexColor(k);

								clothColorsTemp.Add(vertexColorTemp);
							}
						}

						FVertexDetectClothSettingsStruct physicsSettingsAtColorTemp = clothsAndTheirPhysicsSettings_Local.FindRef(skelMeshTemp->GetMeshClothingAssets()[i]);

						auto chaosClothPhysicsSettingsTemp = GetChaosClothPhysicsSettingsBasedOnVertexColors(skelMeshTemp->GetMeshClothingAssets()[i], clothColorsTemp, physicsSettingsAtColorTemp, skeletalMeshComponent, useGivenColorAsAvarageColor, avarageColor);

						VertexPaintFunctions::SetChaosClothPhysics(skeletalMeshComponent, skelMeshTemp->GetMeshClothingAssets()[i], chaosClothPhysicsSettingsTemp);
					}
				}
			}
		}
	}
}


//-------------------------------------------------------

// Get Chaos Cloth Physics Settings Based On Vertex Colors

FVertexDetectChaosClothPhysicsSettings VertexPaintFunctions::GetChaosClothPhysicsSettingsBasedOnVertexColors(UClothingAssetBase* clothingAsset, TArray<FColor> clothColors, FVertexDetectClothSettingsStruct clothPhysicsSettings, USkeletalMeshComponent* skeletalMeshComponent, bool useGivenColorAsAvarageColor, FLinearColor avarageColor) {

	if (!IsValid(skeletalMeshComponent) || !IsValid(clothingAsset)) return FVertexDetectChaosClothPhysicsSettings();


	// https://docs.unrealengine.com/4.27/en-US/API/Plugins/ChaosCloth/ChaosCloth/UChaosClothingInteractor/


	float redAvarageColorValue;
	float greenAvarageColorValue;
	float blueAvarageColorValue;
	float alphaAvarageColorValue;

	// If Setting the entire mesh to be a specific color, then we already know the avarage color and doesn't have to run loops
	if (!useGivenColorAsAvarageColor) {

		FVertexDetectAmountOfPaintedColorsOfEachChannel amountPerChannelTemp = VertexPaintFunctions::GetAmountOfPaintedColorsForEachChannel(clothColors, 0.01f);

		redAvarageColorValue = amountPerChannelTemp.redChannelResult.averageColorAmountAtMinAmount;
		greenAvarageColorValue = amountPerChannelTemp.greenChannelResult.averageColorAmountAtMinAmount;
		blueAvarageColorValue = amountPerChannelTemp.blueChannelResult.averageColorAmountAtMinAmount;
		alphaAvarageColorValue = amountPerChannelTemp.alphaChannelResult.averageColorAmountAtMinAmount;
	}
	else {

		redAvarageColorValue = avarageColor.R;
		greenAvarageColorValue = avarageColor.G;
		blueAvarageColorValue = avarageColor.B;
		alphaAvarageColorValue = avarageColor.A;
	}


	TArray<float> clothPhysicsSettingsAtColorAvarageValue_Local;
	TArray<FVertexDetectClothPhysicsSettingsAtVertexColorStruct> clothPhysicsSettingsAtColor_Local;


	clothPhysicsSettingsAtColorAvarageValue_Local.Add(redAvarageColorValue);
	clothPhysicsSettingsAtColor_Local.Add(clothPhysicsSettings.clothPhysicsSettingsAtRedChannel);

	clothPhysicsSettingsAtColorAvarageValue_Local.Add(greenAvarageColorValue);
	clothPhysicsSettingsAtColor_Local.Add(clothPhysicsSettings.clothPhysicsSettingsAtGreenChannel);

	clothPhysicsSettingsAtColorAvarageValue_Local.Add(blueAvarageColorValue);
	clothPhysicsSettingsAtColor_Local.Add(clothPhysicsSettings.clothPhysicsSettingsAtBlueChannel);

	clothPhysicsSettingsAtColorAvarageValue_Local.Add(alphaAvarageColorValue);
	clothPhysicsSettingsAtColor_Local.Add(clothPhysicsSettings.clothPhysicsSettingsAtAlphaChannel);



	// NOTE Removed the minRequiredPaintAmount to affect Gravity or damping etc. because it caused an issue when Removing colors and trying to reset the cloth, since it couldn't do anything if not above 0.25 or something

	FVertexDetectChaosClothPhysicsSettings chaosClothPhysicsSettingsLocal;

	// Resets all the settings so we base wind lift etc. all from 0 and not += onto the default values
	chaosClothPhysicsSettingsLocal.ResetAllClothSettings();

	for (int i = 0; i < clothPhysicsSettingsAtColor_Local.Num(); i++) {


		// Damping
		if (clothPhysicsSettingsAtColor_Local[i].SetDamping) {

			chaosClothPhysicsSettingsLocal.SetDamping = true;

			chaosClothPhysicsSettingsLocal.clothDampingSettings.SetDamping_dampingCoefficient += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothDampingSettingsWithNoColorPaintedAtChannel.SetDamping_dampingCoefficient, clothPhysicsSettingsAtColor_Local[i].clothDampingSettingsWithFullColorPaintedAtChannel.SetDamping_dampingCoefficient, clothPhysicsSettingsAtColorAvarageValue_Local[i]);
		}

		// Gravity
		if (clothPhysicsSettingsAtColor_Local[i].SetGravity) {

			chaosClothPhysicsSettingsLocal.SetGravity = true;

			chaosClothPhysicsSettingsLocal.clothGravitySettings.SetGravity_gravityScale += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothGravitySettingsWithNoColorPaintedAtChannel.SetGravity_gravityScale, clothPhysicsSettingsAtColor_Local[i].clothGravitySettingsWithFullColorPaintedAtChannel.SetGravity_gravityScale, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothGravitySettings.SetGravity_gravityOverride += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothGravitySettingsWithNoColorPaintedAtChannel.SetGravity_gravityOverride, clothPhysicsSettingsAtColor_Local[i].clothGravitySettingsWithFullColorPaintedAtChannel.SetGravity_gravityOverride, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			// If at least 1 color has set it to override gravity then that is what it will do
			if (clothPhysicsSettingsAtColorAvarageValue_Local[i] > 0.5) {

				// If already true then can't set it to false
				if (!chaosClothPhysicsSettingsLocal.clothGravitySettings.SetGravity_overrideGravity)
					chaosClothPhysicsSettingsLocal.clothGravitySettings.SetGravity_overrideGravity = clothPhysicsSettingsAtColor_Local[i].clothGravitySettingsWithFullColorPaintedAtChannel.SetGravity_overrideGravity;
			}

			else {

				if (!chaosClothPhysicsSettingsLocal.clothGravitySettings.SetGravity_overrideGravity)
					chaosClothPhysicsSettingsLocal.clothGravitySettings.SetGravity_overrideGravity = clothPhysicsSettingsAtColor_Local[i].clothGravitySettingsWithNoColorPaintedAtChannel.SetGravity_overrideGravity;
			}
		}

		// Wind
		if (clothPhysicsSettingsAtColor_Local[i].SetWind) {

			chaosClothPhysicsSettingsLocal.SetWind = true;

			chaosClothPhysicsSettingsLocal.clothWindSettings.SetWind_drag += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithNoColorPaintedAtChannel.SetWind_drag, clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithFullColorPaintedAtChannel.SetWind_drag, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothWindSettings.SetWind_lift += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithNoColorPaintedAtChannel.SetWind_lift, clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithFullColorPaintedAtChannel.SetWind_lift, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothWindSettings.SetWind_airDensity += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithNoColorPaintedAtChannel.SetWind_airDensity, clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithFullColorPaintedAtChannel.SetWind_airDensity, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothWindSettings.SetWind_windVelocity += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithNoColorPaintedAtChannel.SetWind_windVelocity, clothPhysicsSettingsAtColor_Local[i].clothWindSettingsWithFullColorPaintedAtChannel.SetWind_windVelocity, clothPhysicsSettingsAtColorAvarageValue_Local[i]);
		}

		// Anim Drive
		if (clothPhysicsSettingsAtColor_Local[i].SetAnimDrive) {

			chaosClothPhysicsSettingsLocal.SetAnimDrive = true;

			chaosClothPhysicsSettingsLocal.clothAnimDriveSettings.SetAnimDrive_Stiffness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothAnimDriveSettingsWithNoColorPaintedAtChannel.SetAnimDrive_Stiffness, clothPhysicsSettingsAtColor_Local[i].clothAnimDriveSettingsWithFullColorPaintedAtChannel.SetAnimDrive_Stiffness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothAnimDriveSettings.SetAnimDrive_Damping += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothAnimDriveSettingsWithNoColorPaintedAtChannel.SetAnimDrive_Damping, clothPhysicsSettingsAtColor_Local[i].clothAnimDriveSettingsWithFullColorPaintedAtChannel.SetAnimDrive_Damping, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

		}

		// Collision
		if (clothPhysicsSettingsAtColor_Local[i].SetCollision) {

			chaosClothPhysicsSettingsLocal.SetCollision = true;

			chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_CollisionThickness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithNoColorPaintedAtChannel.SetCollision_CollisionThickness, clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithFullColorPaintedAtChannel.SetCollision_CollisionThickness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_FrictionCoefficient += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithNoColorPaintedAtChannel.SetCollision_FrictionCoefficient, clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithFullColorPaintedAtChannel.SetCollision_FrictionCoefficient, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_SelfCollisionThickness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithNoColorPaintedAtChannel.SetCollision_SelfCollisionThickness, clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithFullColorPaintedAtChannel.SetCollision_SelfCollisionThickness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);


			// If at least 1 color has set it to use CCD then that is what it will do
			if (clothPhysicsSettingsAtColorAvarageValue_Local[i] > 0.5) {

				if (!chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_UseCCD)
					chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_UseCCD = clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithFullColorPaintedAtChannel.SetCollision_UseCCD;
			}

			else {

				if (!chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_UseCCD)
					chaosClothPhysicsSettingsLocal.clothCollisionSettings.SetCollision_UseCCD = clothPhysicsSettingsAtColor_Local[i].clothCollisionSettingsWithNoColorPaintedAtChannel.SetCollision_UseCCD;
			}
		}

		// Long Range Attachment
		if (clothPhysicsSettingsAtColor_Local[i].SetLongRangeAttachment) {

			chaosClothPhysicsSettingsLocal.SetLongRangeAttachment = true;

			chaosClothPhysicsSettingsLocal.clothLongRangeAttachmentSettings.LongRangeAttachment_TetherThickness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothLongRangeAttachmentSettingsWithNoColorPaintedAtChannel.LongRangeAttachment_TetherThickness, clothPhysicsSettingsAtColor_Local[i].clothLongRangeAttachmentSettingsWithFullColorPaintedAtChannel.LongRangeAttachment_TetherThickness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothLongRangeAttachmentSettings.LongRangeAttachment_TetherScale += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothLongRangeAttachmentSettingsWithNoColorPaintedAtChannel.LongRangeAttachment_TetherScale, clothPhysicsSettingsAtColor_Local[i].clothLongRangeAttachmentSettingsWithFullColorPaintedAtChannel.LongRangeAttachment_TetherScale, clothPhysicsSettingsAtColorAvarageValue_Local[i]);
		}

		// Material
		if (clothPhysicsSettingsAtColor_Local[i].SetMaterial) {

			chaosClothPhysicsSettingsLocal.SetMaterial = true;

			chaosClothPhysicsSettingsLocal.clothMaterialSettings.Material_EdgeStiffness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothMaterialSettingsWithNoColorPaintedAtChannel.Material_EdgeStiffness, clothPhysicsSettingsAtColor_Local[i].clothMaterialSettingsWithFullColorPaintedAtChannel.Material_EdgeStiffness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothMaterialSettings.Material_BendingStiffness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothMaterialSettingsWithNoColorPaintedAtChannel.Material_BendingStiffness, clothPhysicsSettingsAtColor_Local[i].clothMaterialSettingsWithFullColorPaintedAtChannel.Material_BendingStiffness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothMaterialSettings.Material_AreaStiffness += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothMaterialSettingsWithNoColorPaintedAtChannel.Material_AreaStiffness, clothPhysicsSettingsAtColor_Local[i].clothMaterialSettingsWithFullColorPaintedAtChannel.Material_AreaStiffness, clothPhysicsSettingsAtColorAvarageValue_Local[i]);
		}

		// Physics Velocity Scale
		if (clothPhysicsSettingsAtColor_Local[i].SetPhysicsVelocityScale) {

			chaosClothPhysicsSettingsLocal.SetPhysicsVelocityScale = true;

			chaosClothPhysicsSettingsLocal.clothPhysicsVelocityScaleSettings.PhysicsVelocityScale_LinearVelocityScale += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothPhysicsVelocityScaleSettingsWithNoColorPaintedAtChannel.PhysicsVelocityScale_LinearVelocityScale, clothPhysicsSettingsAtColor_Local[i].clothPhysicsVelocityScaleSettingsWithFullColorPaintedAtChannel.PhysicsVelocityScale_LinearVelocityScale, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothPhysicsVelocityScaleSettings.PhysicVelocityScale_AngularVelocityScale += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothPhysicsVelocityScaleSettingsWithNoColorPaintedAtChannel.PhysicVelocityScale_AngularVelocityScale, clothPhysicsSettingsAtColor_Local[i].clothPhysicsVelocityScaleSettingsWithFullColorPaintedAtChannel.PhysicVelocityScale_AngularVelocityScale, clothPhysicsSettingsAtColorAvarageValue_Local[i]);

			chaosClothPhysicsSettingsLocal.clothPhysicsVelocityScaleSettings.PhysicsVelocityScale_FictitiousAngularVelocityScale += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothPhysicsVelocityScaleSettingsWithNoColorPaintedAtChannel.PhysicsVelocityScale_FictitiousAngularVelocityScale, clothPhysicsSettingsAtColor_Local[i].clothPhysicsVelocityScaleSettingsWithFullColorPaintedAtChannel.PhysicsVelocityScale_FictitiousAngularVelocityScale, clothPhysicsSettingsAtColorAvarageValue_Local[i]);
		}

		// Air Pressure
		if (clothPhysicsSettingsAtColor_Local[i].SetAirPressure) {

			chaosClothPhysicsSettingsLocal.SetAirPressure = true;

			chaosClothPhysicsSettingsLocal.clothPhysicssAirPressureSettings.SetPressure_Pressure += FMath::Lerp(clothPhysicsSettingsAtColor_Local[i].clothPhysicssAirPressureWithNoColorPaintedAtChannel.SetPressure_Pressure, clothPhysicsSettingsAtColor_Local[i].clothPhysicssAirPressureWithFullColorPaintedAtChannel.SetPressure_Pressure, clothPhysicsSettingsAtColorAvarageValue_Local[i]);
		}
	}

	return chaosClothPhysicsSettingsLocal;
}



#endif


//-------------------------------------------------------

// Set Chaos Wheeled Vehicle Friction Multiplier - Made this into a wrapper since in UE4 the function doesn't exist so couldn't have it in BP

void VertexPaintFunctions::SetChaosWheeledVehicleFrictionMultiplier_Wrapper(UChaosWheeledVehicleMovementComponent* chaosWheeledVehicleMovementComponent, int wheelIndex, float friction) {

#if ENGINE_MAJOR_VERSION == 5

	if (!IsValid(chaosWheeledVehicleMovementComponent) || wheelIndex < 0) return;

	chaosWheeledVehicleMovementComponent->SetWheelFrictionMultiplier(wheelIndex, friction);

#endif

}


//-------------------------------------------------------

// Get Physics Surface as String

FString VertexPaintFunctions::GetPhysicsSurfaceAsString(TEnumAsByte<EPhysicalSurface> physicsSurface) {

	if (physicsSurface == EPhysicalSurface::SurfaceType_Default)
		return "Default";

	for (auto physSurfaceNameTemp : GetDefault<UPhysicsSettings>()->PhysicalSurfaces) {

		if (physSurfaceNameTemp.Type == physicsSurface)
			return physSurfaceNameTemp.Name.ToString();
	}

	return FString();
}


//-------------------------------------------------------

// Get Physical Material Using Physics Surface

UPhysicalMaterial* VertexPaintFunctions::GetPhysicalMaterialUsingPhysicsSurface_Wrapper(const UObject* WorldContextObject, TSubclassOf<UPhysicalMaterial> physicalMaterialClass, TEnumAsByte<EPhysicalSurface> physicsSurface) {

	if (physicsSurface == EPhysicalSurface::SurfaceType_Default) return nullptr;
	if (!physicalMaterialClass) return nullptr;
	if (!IsValid(WorldContextObject)) return nullptr;
	if (!IsValid(GetVertexPaintGameInstanceSubsystem(WorldContextObject))) return nullptr;


	if (auto physicsMaterialTemp = GetVertexPaintGameInstanceSubsystem(WorldContextObject)->GetAllCachedPhysicsMaterialAssetss().FindRef(physicsSurface)) {

		// If set to only check in specific class then makes sure that the physical material is that class
		if (physicalMaterialClass->GetClass() && physicsMaterialTemp->GetClass() == physicalMaterialClass) {

			return physicsMaterialTemp;
		}
		else {

			return physicsMaterialTemp;
		}
	}

	return nullptr;
}


//-------------------------------------------------------

// Remove Component From Paint Task Queue

void VertexPaintFunctions::RemoveComponentFromPaintTaskQueue(UPrimitiveComponent* component) {

	if (!IsValid(component)) return;
	if (!IsWorldValid(component->GetWorld())) return;
	if (!IsValid(GetVertexPaintGameInstanceSubsystem(component->GetWorld()))) return;


	if (GetVertexPaintTaskQueue(component->GetWorld()))
		return GetVertexPaintTaskQueue(component->GetWorld())->RemoveMeshComponentFromPaintTaskQueue(component);
}


//-------------------------------------------------------

// Remove Component From Detect Queue

void VertexPaintFunctions::RemoveComponentFromDetectTaskQueue(UPrimitiveComponent* component) {

	if (!IsValid(component)) return;
	if (!IsWorldValid(component->GetWorld())) return;
	if (!IsValid(GetVertexPaintGameInstanceSubsystem(component->GetWorld()))) return;


	if (GetVertexPaintTaskQueue(component->GetWorld()))
		return GetVertexPaintTaskQueue(component->GetWorld())->RemoveMeshComponentFromDetectionTaskQueue(component);
}


//-------------------------------------------------------

// Get Mesh Component Source Mesh

const UObject* VertexPaintFunctions::GetMeshComponentSourceMesh(UPrimitiveComponent* meshComponent) {

	if (!IsValid(meshComponent)) return nullptr;


	const UObject* sourceMeshTemp = nullptr;

	if (auto staticMeshComp = Cast<UStaticMeshComponent>(meshComponent)) {

		sourceMeshTemp = staticMeshComp->GetStaticMesh();
	}

	else if (auto skelMeshComp = Cast<USkeletalMeshComponent>(meshComponent)) {

#if ENGINE_MAJOR_VERSION == 4

		sourceMeshTemp = skelMeshComp->SkeletalMesh;

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

		sourceMeshTemp = skelMeshComp->SkeletalMesh.Get();

#else

		sourceMeshTemp = skelMeshComp->GetSkeletalMeshAsset();

#endif
#endif
	}

#if ENGINE_MAJOR_VERSION == 5

	else if (auto dynamicMeshComponent = Cast<UDynamicMeshComponent>(meshComponent)) {

		// Dynamic Mesh Comps doesn't have a source mesh
	}

	else if (auto geometryCollectionComponent = Cast<UGeometryCollectionComponent>(meshComponent)) {

		sourceMeshTemp = geometryCollectionComponent->GetRestCollection();
	}
#endif

	return sourceMeshTemp;
}


//--------------------------------------------------------

// CalcAABB Without Uniform Check

FBox VertexPaintFunctions::CalcAABBWithoutUniformCheck(const USkinnedMeshComponent* MeshComp, const FTransform& LocalToWorld) {

	// This got copied from UPhysicsAsset::CalcAABB on 1Dec 2023 UE5.0 with just the IsUniform check commented out, since we couldn't use it with Paint Within Area if either X, Y, Z had different scale from one another. 

	FBox Box(ForceInit);

#if ENGINE_MAJOR_VERSION == 5

	if (!MeshComp)
	{
		return Box;
	}

	FVector Scale3D = LocalToWorld.GetScale3D();
	// if (Scale3D.IsUniform())
	// {
	const TArray<int32>* BodyIndexRefs = NULL;
	TArray<int32> AllBodies;
	// If we want to consider all bodies, make array with all body indices in
	if (MeshComp->bConsiderAllBodiesForBounds)
	{
		AllBodies.AddUninitialized(MeshComp->GetPhysicsAsset()->SkeletalBodySetups.Num());
		for (int32 i = 0; i < MeshComp->GetPhysicsAsset()->SkeletalBodySetups.Num(); i++)
		{
			AllBodies[i] = i;
		}
		BodyIndexRefs = &AllBodies;
	}
	// Otherwise, use the cached shortlist of bodies to consider
	else
	{
		BodyIndexRefs = &MeshComp->GetPhysicsAsset()->BoundsBodies;
	}

	// Then iterate over bodies we want to consider, calculating bounding box for each
	const int32 BodySetupNum = (*BodyIndexRefs).Num();

	for (int32 i = 0; i < BodySetupNum; i++)
	{
		const int32 BodyIndex = (*BodyIndexRefs)[i];
		UBodySetup* bs = MeshComp->GetPhysicsAsset()->SkeletalBodySetups[BodyIndex];

		// Check if setup should be considered for bounds, or if all bodies should be considered anyhow
		if (bs->bConsiderForBounds || MeshComp->bConsiderAllBodiesForBounds)
		{
			if (i + 1 < BodySetupNum)
			{
				int32 NextIndex = (*BodyIndexRefs)[i + 1];
				FPlatformMisc::Prefetch(MeshComp->GetPhysicsAsset()->SkeletalBodySetups[NextIndex]);
				FPlatformMisc::Prefetch(MeshComp->GetPhysicsAsset()->SkeletalBodySetups[NextIndex], PLATFORM_CACHE_LINE_SIZE);
			}

			int32 BoneIndex = MeshComp->GetBoneIndex(bs->BoneName);
			if (BoneIndex != INDEX_NONE)
			{
				const FTransform WorldBoneTransform = MeshComp->GetBoneTransform(BoneIndex, LocalToWorld);
				FBox BodySetupBounds = bs->AggGeom.CalcAABB(WorldBoneTransform);

				// When the transform contains a negative scale CalcAABB could return a invalid FBox that has Min and Max reversed
				// @TODO: Maybe CalcAABB should handle that inside and never return a reversed FBox
				if (BodySetupBounds.Min.X > BodySetupBounds.Max.X)
				{
					Swap(BodySetupBounds.Min.X, BodySetupBounds.Max.X);
				}

				if (BodySetupBounds.Min.Y > BodySetupBounds.Max.Y)
				{
					Swap(BodySetupBounds.Min.Y, BodySetupBounds.Max.Y);
				}

				if (BodySetupBounds.Min.Z > BodySetupBounds.Max.Z)
				{
					Swap(BodySetupBounds.Min.Z, BodySetupBounds.Max.Z);
				}

				Box += BodySetupBounds;
			}
		}
	}
	//}
	// else
	//{
	//	UE_LOG(LogPhysics, Log, TEXT("UPhysicsAsset::CalcAABB : Non-uniform scale factor. You will not be able to collide with it.  Turn off collision and wrap it with a blocking volume.  MeshComp: %s  SkelMesh: %s"), *MeshComp->GetFullName(), MeshComp->SkeletalMesh ? *MeshComp->SkeletalMesh->GetFullName() : TEXT("NULL"));
	//}

	if (!Box.IsValid)
	{
		Box = FBox(LocalToWorld.GetLocation(), LocalToWorld.GetLocation());
	}

	const float MinBoundSize = 1.f;
	const FVector BoxSize = Box.GetSize();

	if (BoxSize.GetMin() < MinBoundSize)
	{
		const FVector ExpandByDelta(FMath::Max<FVector::FReal>(0, MinBoundSize - BoxSize.X), FMath::Max<FVector::FReal>(0, MinBoundSize - BoxSize.Y), FMath::Max<FVector::FReal>(0, MinBoundSize - BoxSize.Z));
		Box = Box.ExpandBy(ExpandByDelta * 0.5f);	//expand by applies to both directions with GetSize applies to total size so divide by 2
	}

#elif ENGINE_MAJOR_VERSION == 4

	if (!MeshComp)
	{
		return Box;
	}

	FVector Scale3D = LocalToWorld.GetScale3D();
	// if (Scale3D.IsUniform())
	// {
	const TArray<int32>* BodyIndexRefs = NULL;
	TArray<int32> AllBodies;
	// If we want to consider all bodies, make array with all body indices in
	if (MeshComp->bConsiderAllBodiesForBounds)
	{
		AllBodies.AddUninitialized(MeshComp->GetPhysicsAsset()->SkeletalBodySetups.Num());
		for (int32 i = 0; i < MeshComp->GetPhysicsAsset()->SkeletalBodySetups.Num(); i++)
		{
			AllBodies[i] = i;
		}
		BodyIndexRefs = &AllBodies;
	}
	// Otherwise, use the cached shortlist of bodies to consider
	else
	{
		BodyIndexRefs = &MeshComp->GetPhysicsAsset()->BoundsBodies;
	}

	// Then iterate over bodies we want to consider, calculating bounding box for each
	const int32 BodySetupNum = (*BodyIndexRefs).Num();

	for (int32 i = 0; i < BodySetupNum; i++)
	{
		const int32 BodyIndex = (*BodyIndexRefs)[i];
		UBodySetup* bs = MeshComp->GetPhysicsAsset()->SkeletalBodySetups[BodyIndex];

		// Check if setup should be considered for bounds, or if all bodies should be considered anyhow
		if (bs->bConsiderForBounds || MeshComp->bConsiderAllBodiesForBounds)
		{
			if (i + 1 < BodySetupNum)
			{
				int32 NextIndex = (*BodyIndexRefs)[i + 1];
				FPlatformMisc::Prefetch(MeshComp->GetPhysicsAsset()->SkeletalBodySetups[NextIndex]);
				FPlatformMisc::Prefetch(MeshComp->GetPhysicsAsset()->SkeletalBodySetups[NextIndex], PLATFORM_CACHE_LINE_SIZE);
			}

			int32 BoneIndex = MeshComp->GetBoneIndex(bs->BoneName);
			if (BoneIndex != INDEX_NONE)
			{
				const FTransform WorldBoneTransform = MeshComp->GetBoneTransform(BoneIndex, LocalToWorld);
				FBox BodySetupBounds = bs->AggGeom.CalcAABB(WorldBoneTransform);

				// When the transform contains a negative scale CalcAABB could return a invalid FBox that has Min and Max reversed
				// @TODO: Maybe CalcAABB should handle that inside and never return a reversed FBox
				if (BodySetupBounds.Min.X > BodySetupBounds.Max.X)
				{
					Swap<float>(BodySetupBounds.Min.X, BodySetupBounds.Max.X);
				}

				if (BodySetupBounds.Min.Y > BodySetupBounds.Max.Y)
				{
					Swap<float>(BodySetupBounds.Min.Y, BodySetupBounds.Max.Y);
				}

				if (BodySetupBounds.Min.Z > BodySetupBounds.Max.Z)
				{
					Swap<float>(BodySetupBounds.Min.Z, BodySetupBounds.Max.Z);
				}

				Box += BodySetupBounds;
			}
		}
	}
	// }
	// else
	//{
	//	UE_LOG(LogPhysics, Log, TEXT("UPhysicsAsset::CalcAABB : Non-uniform scale factor. You will not be able to collide with it.  Turn off collision and wrap it with a blocking volume.  MeshComp: %s  SkelMesh: %s"), *MeshComp->GetFullName(), MeshComp->SkeletalMesh ? *MeshComp->SkeletalMesh->GetFullName() : TEXT("NULL"));
	//}

	if (!Box.IsValid)
	{
		Box = FBox(LocalToWorld.GetLocation(), LocalToWorld.GetLocation());
	}

	const float MinBoundSize = 1.f;
	const FVector BoxSize = Box.GetSize();

	if (BoxSize.GetMin() < MinBoundSize)
	{
		const FVector ExpandByDelta(FMath::Max(0.f, MinBoundSize - BoxSize.X), FMath::Max(0.f, MinBoundSize - BoxSize.Y), FMath::Max(0.f, MinBoundSize - BoxSize.Z));
		Box = Box.ExpandBy(ExpandByDelta * 0.5f);	//expand by applies to both directions with GetSize applies to total size so divide by 2
	}

#endif

	return Box;
}


//--------------------------------------------------------

// Get All Physics Surfaces

TArray<TEnumAsByte<EPhysicalSurface>> VertexPaintFunctions::GetAllPhysicsSurfaces() {

	TArray<TEnumAsByte<EPhysicalSurface>> physicalSurfaces_Local;

	TEnumAsByte<EPhysicalSurface> cachedPhysicalSurface = EPhysicalSurface::SurfaceType1;

	for (int i = 0; i < GetDefault<UPhysicsSettings>()->PhysicalSurfaces.Num(); i++) {

		auto physSurfaceNameTemp = GetDefault<UPhysicsSettings>()->PhysicalSurfaces[i];


		/*
		Checks if the first elements, or if any elements in between physics surfaces are None, if so, we have to Add whatever Surface Type is meant to be there, so filling surfaces to choose from in the Editor Widget, they match what actual surface type we can select.

		For example if there is a Gap between Surface type 12 and 14, where 13 is None, then it won't be apart of GetDefault<UPhysicsSettings>()->PhysicalSurfaces, so if we fill a drop down list without it, and select a physics surface that comes After 13, then the selected index from the drop down list will not match the actual physics surface we selected because the amount is different. The total amount up to the last registered physics surface may be 18, but we only get 17 because 13 is None, which means we may think we select 17 but actually getting 16, meaning the wrong thing was registered at the vertex color channel than the user intended.

		So to fix this we simply Add onto the list we return with the missing physics surface, so we actually return the complete list up until the very last registered physics surface.

		This should be a pretty rare edge case but better to safeguard so no one runs into this issue.
		*/


		// If at the first element
		if (i == 0) {

			// but first registered physics surface is more than 1, then we manually add SurfaceType1, 2 etc. until we reach whatever element the first actually registered phys surface is. 
			if (physSurfaceNameTemp.Type.GetValue() > 1) {

				// UE_LOG(LogTemp, Warning, TEXT("First Element - the first registered physics starts later so have to add each default surface type until we reach it. %i"), physSurfaceNameTemp.Type.GetValue());

				for (int j = 1; j < physSurfaceNameTemp.Type.GetValue(); j++) {

					cachedPhysicalSurface = static_cast<EPhysicalSurface>(j);
					physicalSurfaces_Local.Add(cachedPhysicalSurface);

					// UE_LOG(LogTemp, Warning, TEXT("Adding missing first elements: %i"), cachedPhysicalSurface.GetValue());
				}


				// When finished filling in default physics surfaces, then we add the actually first registered physics surface
				physicalSurfaces_Local.Add(physSurfaceNameTemp.Type);
			}


			else {

				physicalSurfaces_Local.Add(physSurfaceNameTemp.Type);
			}
		}

		// If it has skipped a element, for example jumped from 12 to 15, indicating that 13 and 14 is None, then we add the missing surface
		else if (cachedPhysicalSurface.GetValue() + 1 != physSurfaceNameTemp.Type.GetValue()) {


			int differentTemp = physSurfaceNameTemp.Type.GetValue() - (cachedPhysicalSurface.GetValue() + 1);

			// UE_LOG(LogTemp, Warning, TEXT("Missmatch: %i  -  %i  -  diff: %i"), (test.GetValue() + 1), physSurfaceNameTemp.Type.GetValue(), differentTemp);

			for (int j = 0; j < differentTemp; j++) {

				cachedPhysicalSurface = static_cast<EPhysicalSurface>(cachedPhysicalSurface.GetValue() + 1);
				physicalSurfaces_Local.Add(cachedPhysicalSurface);

				// UE_LOG(LogTemp, Warning, TEXT("Adding missing elements: %i"), (test.GetValue() + 1));
			}


			// When finished filling in physics surfaces in between where there where Nones, then we add the registered physics surface
			physicalSurfaces_Local.Add(physSurfaceNameTemp.Type);
		}


		// If the next physics surface is the expected value then just adds it
		else if (cachedPhysicalSurface.GetValue() + 1 == physSurfaceNameTemp.Type.GetValue()) {

			physicalSurfaces_Local.Add(physSurfaceNameTemp.Type);
		}


		// Caches the latest one so we can check against it the next loop if there is a diff to what we expect
		cachedPhysicalSurface = physSurfaceNameTemp.Type;
	}

	return physicalSurfaces_Local;
}


#if WITH_EDITOR


//--------------------------------------------------------

// Get Objects Of Class

TArray<UObject*> VertexPaintFunctions::VertexPaintFunctionsLib_GetObjectsOfClass(TSubclassOf<UObject> objectsToGet, bool onlyGetObjectsFromContentFolder) {

	if (!objectsToGet.Get()) return TArray<UObject*>();


	FAssetRegistryModule& AssetRegistryModule_Local = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData_Local;
	TArray<UObject*> objects_Local;


#if ENGINE_MAJOR_VERSION == 4

	AssetRegistryModule_Local.Get().GetAssetsByClass(objectsToGet.Get()->GetFName(), AssetData_Local);

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

	AssetRegistryModule_Local.Get().GetAssetsByClass(objectsToGet.Get()->GetFName(), AssetData_Local);


#else

	AssetRegistryModule_Local.Get().GetAssetsByClass(objectsToGet.Get()->GetClassPathName(), AssetData_Local);

#endif
#endif


	for (auto asset_Local : AssetData_Local) {


		// If asset it not in the content folder
		if (!asset_Local.ToSoftObjectPath().ToString().StartsWith("/Game", ESearchCase::IgnoreCase)) {

			if (onlyGetObjectsFromContentFolder)
				continue;
		}

		if (asset_Local.GetAsset())
			objects_Local.Add(asset_Local.GetAsset());
	}

	return objects_Local;
}

//--------------------------------------------------------

// Get Soft Object Path From Soft Object Ptr

FSoftObjectPath VertexPaintFunctions::VertexPaintFunctionsLib_GetSoftObjectPathFromSoftObjectPtr(TSoftObjectPtr<UObject> object) {

	if (!object) return FSoftObjectPath();

	return object.ToSoftObjectPath();
}


//--------------------------------------------------------

// Get Soft Object Name From Soft Object Ptr

FString VertexPaintFunctions::VertexPaintFunctionsLib_GetObjectNameFromSoftObjectPtr(TSoftObjectPtr<UObject> object) {

	if (!object) return FString();

	return object.GetAssetName();
}


//--------------------------------------------------------

// Get Object Of Class as Soft Ptrs

TArray<TSoftObjectPtr<UObject>> VertexPaintFunctions::VertexPaintFunctionsLib_GetObjectsOfClassAsSoftPtrs(TSubclassOf<UObject> objectsToGet, bool loadObjects) {

	if (!objectsToGet.Get()) return TArray<TSoftObjectPtr<UObject>>();


	FAssetRegistryModule& AssetRegistryModule_Local = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetData_Local;


#if ENGINE_MAJOR_VERSION == 4

	AssetRegistryModule_Local.Get().GetAssetsByClass(objectsToGet.Get()->GetFName(), AssetData_Local);

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

	AssetRegistryModule_Local.Get().GetAssetsByClass(objectsToGet.Get()->GetFName(), AssetData_Local);


#else

	AssetRegistryModule_Local.Get().GetAssetsByClass(objectsToGet.Get()->GetClassPathName(), AssetData_Local);

#endif
#endif


	TArray<TSoftObjectPtr<UObject>> softObjectPtrs_Local;
	TSoftObjectPtr<UObject> tempSoftObject;

	for (auto asset_Local : AssetData_Local) {


		// If asset it not in the content folder
		if (!asset_Local.ToSoftObjectPath().ToString().StartsWith("/Game", ESearchCase::IgnoreCase)) {

			continue;
		}

		tempSoftObject = asset_Local.ToSoftObjectPath();


		if (loadObjects)
			tempSoftObject.LoadSynchronous();

		if (!tempSoftObject) continue;

		softObjectPtrs_Local.Add(tempSoftObject);
	}

	return softObjectPtrs_Local;
}


#endif


//-------------------------------------------------------

// Fill Calculate Colors Info Fundementals

void VertexPaintFunctions::FillCalculateColorsInfoFundementals(const FVertexDetectFundementalStruct& fundementalStruct, FCalculateColorsInfo& calculateColorsInfo) {

	if (!IsValid(fundementalStruct.meshComponent)) return;


	UStaticMeshComponent* staticMeshComponentTemp = nullptr;
	USplineMeshComponent* splineMeshComponentTemp = nullptr;
	USkeletalMeshComponent* skeletalMeshComponentTemp = nullptr;
	UInstancedStaticMeshComponent* instancedStaticMeshComponentTemp = nullptr;

	staticMeshComponentTemp = Cast<UStaticMeshComponent>(fundementalStruct.meshComponent);

	if (staticMeshComponentTemp) {

		splineMeshComponentTemp = Cast<USplineMeshComponent>(fundementalStruct.meshComponent);

		if (!splineMeshComponentTemp)
			instancedStaticMeshComponentTemp = Cast<UInstancedStaticMeshComponent>(fundementalStruct.meshComponent);
	}
	else {

		skeletalMeshComponentTemp = Cast<USkeletalMeshComponent>(fundementalStruct.meshComponent);
	}


#if ENGINE_MAJOR_VERSION == 5

	UDynamicMeshComponent* dynamicMeshComponentTemp = nullptr;
	UGeometryCollectionComponent* geometryCollectionCompTemp = nullptr;

	if (!staticMeshComponentTemp && !skeletalMeshComponentTemp) {

		dynamicMeshComponentTemp = Cast<UDynamicMeshComponent>(fundementalStruct.meshComponent);

		if (!dynamicMeshComponentTemp)
			geometryCollectionCompTemp = Cast<UGeometryCollectionComponent>(fundementalStruct.meshComponent);
	}

#endif


	const UObject* sourceMeshTemp = VertexPaintFunctions::GetMeshComponentSourceMesh(fundementalStruct.meshComponent);


	USkeletalMesh* skelMeshTemp = nullptr;
	USkinnedMeshComponent* skinnedMeshComp_Local = nullptr;
	USkinnedMeshComponent* skinnedMasterComp_Local = nullptr;

	if (skeletalMeshComponentTemp) {

		skeletalMeshComponentTemp->GetBoneNames(calculateColorsInfo.skeletalMeshBonesNames);
		skinnedMeshComp_Local = skeletalMeshComponentTemp;

#if ENGINE_MAJOR_VERSION == 4

		skelMeshTemp = skeletalMeshComponentTemp->SkeletalMesh;

		// If it has a Master Component then we had to use that when calling CacheRefToLocalMatrices, otherwise we got a crash
		if (skeletalMeshComponentTemp->MasterPoseComponent.Get())
			skinnedMasterComp_Local = skeletalMeshComponentTemp->MasterPoseComponent.Get();


#elif ENGINE_MAJOR_VERSION == 5


#if ENGINE_MINOR_VERSION == 0

		skelMeshTemp = skeletalMeshComponentTemp->SkeletalMesh.Get();

		// If it has a Master Component then we had to use that when calling CacheRefToLocalMatrices, otherwise we got a crash
		if (skeletalMeshComponentTemp->MasterPoseComponent.Get())
			skinnedMasterComp_Local = skeletalMeshComponentTemp->MasterPoseComponent.Get();

#else

		skelMeshTemp = skeletalMeshComponentTemp->GetSkeletalMeshAsset();

		// If it has a Master Component then we had to use that when calling CacheRefToLocalMatrices, otherwise we got a crash
		if (skeletalMeshComponentTemp->LeaderPoseComponent.Get())
			skinnedMasterComp_Local = skeletalMeshComponentTemp->LeaderPoseComponent.Get();

#endif
#endif

		// Only if we actually had a Master component we set the MasterSkinned to that, ohterwise the skeletal mesh comp is the Master
		if (skinnedMasterComp_Local)
			calculateColorsInfo.vertexPaintSkelComponentsMasterSkinnedComp = skinnedMasterComp_Local;
		else
			calculateColorsInfo.vertexPaintSkelComponentsMasterSkinnedComp = skeletalMeshComponentTemp;
	}


	// If paint job
	if (calculateColorsInfo.vertexPaintSettings.actor) {

		calculateColorsInfo.lodsToLoopThrough = VertexPaintFunctions::GetAmountOfLODsToPaintOn(fundementalStruct.meshComponent, calculateColorsInfo.vertexPaintSettings.overrideLOD.overrideLODToPaintUpTo, calculateColorsInfo.vertexPaintSettings.overrideLOD.amountOfLODsToPaint);
	}

	// If just Detecting and set to only include vertex data for lod 0 in the callback, there's no reason to loop through more LODs, unlike painting where even you may still need to paint on all LODs eventhough you only want LOD0 in the callback. 
	else if (calculateColorsInfo.getClosestVertexDataSettings.actor || calculateColorsInfo.getAllVertexColorsSettings.actor) {

		if (calculateColorsInfo.getClosestVertexDataSettings.callbackSettings.includeVertexDataOnlyForLOD0)
			calculateColorsInfo.lodsToLoopThrough = 1;
	}

	if (calculateColorsInfo.initiatedByComponent)
		calculateColorsInfo.taskResult.associatedPaintComponent = calculateColorsInfo.initiatedByComponent;

	calculateColorsInfo.initialMeshVertexData.meshComp = fundementalStruct.meshComponent;
	calculateColorsInfo.initialMeshVertexData.meshSource = sourceMeshTemp;
	calculateColorsInfo.initialMeshVertexData.meshDataPerLOD.SetNum(calculateColorsInfo.lodsToLoopThrough, true);

	for (int i = 0; i < calculateColorsInfo.initialMeshVertexData.meshDataPerLOD.Num(); i++)
		calculateColorsInfo.initialMeshVertexData.meshDataPerLOD[i].lod = i;

	calculateColorsInfo.taskResult.meshVertexData = calculateColorsInfo.initialMeshVertexData; // Sets this as well in case the task immediately fails in between filling this and starting task, so we atleast can return the meshComp etc. with the task result. 
	calculateColorsInfo.vertexPaintActor = fundementalStruct.meshComponent->GetOwner();
	calculateColorsInfo.vertexPaintComponent = fundementalStruct.meshComponent;
	calculateColorsInfo.vertexPaintStaticMeshComponent = staticMeshComponentTemp;
	calculateColorsInfo.vertexPaintSplineMeshComponent = splineMeshComponentTemp; 
	calculateColorsInfo.vertexPaintInstancedStaticMeshComponent = instancedStaticMeshComponentTemp;
	calculateColorsInfo.vertexPaintSkelComponent = skeletalMeshComponentTemp;
	calculateColorsInfo.vertexPaintSkelComponentsSkeletalMesh = skelMeshTemp;
	calculateColorsInfo.vertexPaintSkelComponentsSkinnedMeshComp = skinnedMeshComp_Local;
	calculateColorsInfo.vertexPaintSourceMesh = sourceMeshTemp;
	calculateColorsInfo.vertexPaintMaterialDataAsset = VertexPaintFunctions::GetVertexPaintMaterialDataAsset(fundementalStruct.meshComponent);
	calculateColorsInfo.fundementalStruct = fundementalStruct;
	calculateColorsInfo.fundementalStruct.taskWorld = fundementalStruct.meshComponent->GetWorld();
	calculateColorsInfo.worldTaskWasCreatedIn = fundementalStruct.meshComponent->GetWorld(); // Had to cache the world as well in case component or actor wasn't valid when the task was finished, but we needed to check if the world was valid and start reset timers etc. 

#if ENGINE_MAJOR_VERSION == 5
	calculateColorsInfo.vertexPaintDynamicMeshComponent = dynamicMeshComponentTemp;

	if (geometryCollectionCompTemp) {

		UGeometryCollection* geometryCollection = nullptr;

		geometryCollection = const_cast<UGeometryCollection*>(geometryCollectionCompTemp->GetRestCollection());

		if (geometryCollection) {

			calculateColorsInfo.vertexPaintGeometryCollectionComponent = geometryCollectionCompTemp;
			calculateColorsInfo.vertexPaintGeometryCollection = geometryCollection;
			calculateColorsInfo.vertexPaintGeometryCollectionData = geometryCollection->GetGeometryCollection().Get();
		}
	}



#endif

	// If set to compare mesh colors to a color array, either serialized och TArray, one of them has to be set, otherwise we set it to false so we don't loop through vertices for no reason if for instance a color snippet and this was true. 
	if (calculateColorsInfo.fundementalStruct.callbackSettings.compareMeshColorsToColorArray.compareMeshColorsToColorArrayAtLOD0 && calculateColorsInfo.fundementalStruct.callbackSettings.compareMeshColorsToColorArray.colorArrayToCompareWith.Num() <= 0) {

		calculateColorsInfo.fundementalStruct.callbackSettings.compareMeshColorsToColorArray.compareMeshColorsToColorArrayAtLOD0 = false;
	}


	// Paint Color Snippets, Set Mesh Component Verte Colors regularly or with Serialized String only use LOD0 data, so for them we always propogate to other LODs. Paint Randomly over the Entire Mesh however has the option to do this since you might want to randomize on each LOD to save performance
	if (calculateColorsInfo.paintOnColorSnippetSettings.actor || calculateColorsInfo.setMeshComponentVertexColorsSettings.actor || calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings.actor || (calculateColorsInfo.paintOnEntireMeshSettings.actor && calculateColorsInfo.paintOnEntireMeshSettings.paintOnRandomVerticesSettings.paintAtRandomVerticesSpreadOutOverTheEntireMesh && calculateColorsInfo.paintOnEntireMeshSettings.paintOnRandomVerticesSettings.paintAtRandomVerticesSpreadOutOverTheEntireMesh_PropogateLOD0ToAllLODsMethod == Enum_PaintEntireMeshAtRandomVertices_PropogateToLODsMethod::ModifiedEngineMethod)) {

		if (calculateColorsInfo.lodsToLoopThrough > 1)
			calculateColorsInfo.propogateLOD0ToAllLODs = true;
	}


	if (fundementalStruct.multiThreadSettings.useMultithreadingForCalculations) {

		if (calculateColorsInfo.fundementalStruct.debugSettings.atGameThread_drawVertexPositionDebugPoint || calculateColorsInfo.fundementalStruct.debugSettings.atGameThread_drawVertexPositionDebugPointOnVertexThatGotPaintApplied || calculateColorsInfo.fundementalStruct.debugSettings.atGameThread_drawClothVertexPositionDebugPoint || calculateColorsInfo.fundementalStruct.debugSettings.atGameThread_drawVertexNormalDebugArrow) {


			VertexPaintFunctions::PrintTaskLog(fundementalStruct.debugSettings, FString::Printf(TEXT("VertexPaint - Paint/Detect Task is set to Draw Debug Symbols at Vertices but it only works if not Multithreading, i.e. on the Game Thread.")), FColor::Orange);
		}
	}

	// If Paint Job
	if (calculateColorsInfo.vertexPaintSettings.actor) {


		// For Paint Jobs that set colors directly like ColorSnippet and SetMeshComponentColors, we're not specifying any channel that we apply color to, so adds all of them. 
		if (!calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyVertexColorUsingPhysicsSurface && calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyVertexColorSetting == EApplyVertexColorSetting::ESetVertexColor || calculateColorsInfo.paintOnColorSnippetSettings.actor || calculateColorsInfo.paintDetectionType == EVertexPaintDetectionType::SetMeshVertexColorsDirectly || calculateColorsInfo.paintDetectionType == EVertexPaintDetectionType::SetMeshVertexColorsDirectlyUsingSerializedString) {

			calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::RedChannel);
			calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::GreenChannel);
			calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::BlueChannel);
			calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::AlphaChannel);
		}


		// If paint job where you set strength of colors to Apply and can have paint conditions for them
		if (calculateColorsInfo.paintOnMeshColorSettings.actor) {


			// If not painting using physics surface but the regular way, then if Add, and not 0 then that channel we will apply colors to (eventhough there may not be a difference but we will try). If painting with physics surface, then we will be able to get which surface is on which channel when looping through the mesh sections so this gets added there. 
			if (!calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyVertexColorUsingPhysicsSurface) {

				if (calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyVertexColorSetting == EApplyVertexColorSetting::EAddVertexColor) {

					if (calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.redColor != 0)
						calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::RedChannel);

					if (calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.greenColor != 0)
						calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::GreenChannel);

					if (calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.blueColor != 0)
						calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::BlueChannel);

					if (calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.alphaColor != 0)
						calculateColorsInfo.paintTaskResult.colorAppliedToVertexColorChannels.Add(EVertexColorChannel::AlphaChannel);
				}
			}


			// Gets the Actor Location for only affect vertices with direction if it has been set. 
			if (calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation.onlyAffectVerticesWithDirectionToActorOrLocation) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation.actor)) {

					calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation.location = calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation.actor->GetActorLocation();
				}
			}


			// Gets Actor Location for Line of Sight Paint Condition if the actor has been set
			for (int i = 0; i < calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.redColorCondition.ifVertexHasLineOfSightTo.Num(); i++) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.redColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor)) {

					calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.redColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToPosition = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.redColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor->GetActorLocation();
				}
			}

			for (int i = 0; i < calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.greenColorCondition.ifVertexHasLineOfSightTo.Num(); i++) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.greenColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor)) {

					calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.greenColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToPosition = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.greenColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor->GetActorLocation();
				}
			}

			for (int i = 0; i < calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.blueColorCondition.ifVertexHasLineOfSightTo.Num(); i++) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.blueColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor)) {

					calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.blueColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToPosition = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.blueColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor->GetActorLocation();
				}
			}

			for (int i = 0; i < calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.alphaColorCondition.ifVertexHasLineOfSightTo.Num(); i++) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.alphaColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor)) {

					calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.alphaColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToPosition = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.alphaColorCondition.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor->GetActorLocation();
				}
			}

			for (int i = 0; i < calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintUsingPhysicsSurfaceConditions.ifVertexHasLineOfSightTo.Num(); i++) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintUsingPhysicsSurfaceConditions.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor)) {

					calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintUsingPhysicsSurfaceConditions.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToPosition = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintUsingPhysicsSurfaceConditions.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor->GetActorLocation();
				}
			}

			for (int i = 0; i < calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintConditionsOnChannelsWithoutThePhysicsSurface.ifVertexHasLineOfSightTo.Num(); i++) {

				if (IsValid(calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintConditionsOnChannelsWithoutThePhysicsSurface.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor)) {

					calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintConditionsOnChannelsWithoutThePhysicsSurface.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToPosition = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintConditionsOnChannelsWithoutThePhysicsSurface.ifVertexHasLineOfSightTo[i].ifVertexHasLineOfSightToActor->GetActorLocation();
				}
			}


			// Updates the invidual struct settings as well so they match the paintOnMeshColorSettings, in case we for some reason try to access the condition things we've set above through them. Shouldn't be necessary i think but just in case 
			switch (calculateColorsInfo.paintDetectionType) {

			case EVertexPaintDetectionType::GetClosestVertexDataDetection:
				break;

			case EVertexPaintDetectionType::GetAllVertexColorDetection:
				break;

			case EVertexPaintDetectionType::PaintAtLocation:
				calculateColorsInfo.paintOnMeshAtLocationSettings.applyVertexColorSettings = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings;
				calculateColorsInfo.paintOnMeshAtLocationSettings.onlyAffectVerticesWithDirectionToLocation = calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation;
				break;

			case EVertexPaintDetectionType::PaintWithinArea:
				calculateColorsInfo.paintOnMeshWithinAreaSettings.applyVertexColorSettings = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings;
				calculateColorsInfo.paintOnMeshWithinAreaSettings.onlyAffectVerticesWithDirectionToLocation = calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation;
				break;

			case EVertexPaintDetectionType::PaintEntireMesh:
				calculateColorsInfo.paintOnEntireMeshSettings.applyVertexColorSettings = calculateColorsInfo.paintOnMeshColorSettings.applyVertexColorSettings;
				calculateColorsInfo.paintOnEntireMeshSettings.onlyAffectVerticesWithDirectionToLocation = calculateColorsInfo.paintOnMeshColorSettings.onlyAffectVerticesWithDirectionToLocation;
				break;

			case EVertexPaintDetectionType::PaintColorSnippet:
				break;

			case EVertexPaintDetectionType::SetMeshVertexColorsDirectly:
				break;

			case EVertexPaintDetectionType::SetMeshVertexColorsDirectlyUsingSerializedString:
				break;

			default:
				break;
			}
		}
	}
}


//-------------------------------------------------------

// Callbacks

void VertexPaintFunctions::RunGetClosestVertexDataCallbacks(const FCalculateColorsInfo& calculateColorsInfo, const FVertexDetectClosestVertexDataResultStruct& closestVertexColorResult, const FVertexDetectEstimatedColorAtHitLocationResultStruct& estimatedColorAtHitLocationResult, const FVertexDetectAvarageColorInAreaInfo& avarageColor) {

	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		calculateColorsInfo.initiatedByComponent->GetClosestVertexDataOnMeshTaskFinished(calculateColorsInfo, closestVertexColorResult, estimatedColorAtHitLocationResult, avarageColor);
	}

	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		if (calculateColorsInfo.getClosestVertexDataSettings.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_GetClosestVertexDataOnActor(calculateColorsInfo.getClosestVertexDataSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.getClosestVertexDataSettings, closestVertexColorResult, estimatedColorAtHitLocationResult, avarageColor, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
					IVertexPaintDetectionInterface::Execute_GetClosestVertexDataOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.getClosestVertexDataSettings, closestVertexColorResult, estimatedColorAtHitLocationResult, avarageColor, calculateColorsInfo.additionalDataToPassThrough);
			}
		}
	}
}

void VertexPaintFunctions::RunGetAllColorsOnlyCallbacks(const FCalculateColorsInfo& calculateColorsInfo) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		calculateColorsInfo.initiatedByComponent->GetAllVertexColorsOnlyTaskFinished(calculateColorsInfo);
	}


	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		if (calculateColorsInfo.getAllVertexColorsSettings.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_GetAllVertexColorsOnlyOnActor(calculateColorsInfo.getAllVertexColorsSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.getAllVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
					IVertexPaintDetectionInterface::Execute_GetAllVertexColorsOnlyOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.getAllVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);
			}
		}
	}
}

void VertexPaintFunctions::RunPaintAtLocationCallbacks(const FCalculateColorsInfo& calculateColorsInfo, const FVertexDetectClosestVertexDataResultStruct& closestVertexColorResult, const FVertexDetectEstimatedColorAtHitLocationResultStruct& estimatedColorAtHitLocationResult, const FVertexDetectAvarageColorInAreaInfo& avarageColor) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		calculateColorsInfo.initiatedByComponent->PaintOnMeshAtLocationTaskFinished(calculateColorsInfo, closestVertexColorResult, estimatedColorAtHitLocationResult, avarageColor);
	}

	
	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_PaintedOnActor_AtLocation(calculateColorsInfo.paintOnMeshAtLocationSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshAtLocationSettings, closestVertexColorResult, estimatedColorAtHitLocationResult, avarageColor, calculateColorsInfo.additionalDataToPassThrough);

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(calculateColorsInfo.vertexPaintActor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshAtLocationSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass())) {

					IVertexPaintDetectionInterface::Execute_PaintedOnActor_AtLocation(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshAtLocationSettings, closestVertexColorResult, estimatedColorAtHitLocationResult, avarageColor, calculateColorsInfo.additionalDataToPassThrough);

					IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshAtLocationSettings, calculateColorsInfo.additionalDataToPassThrough);
				}
			}
		}
	}
}

void VertexPaintFunctions::RunPaintWithinAreaCallbacks(const FCalculateColorsInfo& calculateColorsInfo) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		calculateColorsInfo.initiatedByComponent->PaintOnMeshWithinAreaTaskFinished(calculateColorsInfo);
	}


	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_PaintedOnActor_WithinArea(calculateColorsInfo.paintOnMeshWithinAreaSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshWithinAreaSettings, calculateColorsInfo.additionalDataToPassThrough);

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(calculateColorsInfo.vertexPaintActor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshWithinAreaSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass())) {

					IVertexPaintDetectionInterface::Execute_PaintedOnActor_WithinArea(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshWithinAreaSettings, calculateColorsInfo.additionalDataToPassThrough);

					IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnMeshWithinAreaSettings, calculateColorsInfo.additionalDataToPassThrough);
				}
			}
		}
	}
}

void VertexPaintFunctions::RunPaintEntireMeshCallbacks(const FCalculateColorsInfo& calculateColorsInfo) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		calculateColorsInfo.initiatedByComponent->PaintOnEntireMeshTaskFinished(calculateColorsInfo);
	}


	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_PaintedOnActor_EntireMesh(calculateColorsInfo.paintOnEntireMeshSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnEntireMeshSettings, calculateColorsInfo.additionalDataToPassThrough);

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(calculateColorsInfo.vertexPaintActor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnEntireMeshSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass())) {

					IVertexPaintDetectionInterface::Execute_PaintedOnActor_EntireMesh(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnEntireMeshSettings, calculateColorsInfo.additionalDataToPassThrough);

					IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnEntireMeshSettings, calculateColorsInfo.additionalDataToPassThrough);
				}
			}
		}
	}
}

void VertexPaintFunctions::RunPaintColorSnippetCallbacks(const FCalculateColorsInfo& calculateColorsInfo) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		calculateColorsInfo.initiatedByComponent->PaintColorSnippetOnMeshTaskFinished(calculateColorsInfo);
	}

	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_PaintedOnActor_PaintColorSnippet(calculateColorsInfo.paintOnColorSnippetSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnColorSnippetSettings, calculateColorsInfo.additionalDataToPassThrough);

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(calculateColorsInfo.vertexPaintActor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnColorSnippetSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass())) {

					IVertexPaintDetectionInterface::Execute_PaintedOnActor_PaintColorSnippet(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnColorSnippetSettings, calculateColorsInfo.additionalDataToPassThrough);

					IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.paintOnColorSnippetSettings, calculateColorsInfo.additionalDataToPassThrough);
				}
			}
		}
	}
}

void VertexPaintFunctions::RunPaintSetMeshColorsCallbacks(const FCalculateColorsInfo& calculateColorsInfo) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackDelegate)
			calculateColorsInfo.initiatedByComponent->vertexColorsSetMeshColorsDelegate.Broadcast(calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);
	}

	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_PaintedOnActor_SetMeshComponentVertexColors(calculateColorsInfo.setMeshComponentVertexColorsSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(calculateColorsInfo.vertexPaintActor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass())) {

					IVertexPaintDetectionInterface::Execute_PaintedOnActor_SetMeshComponentVertexColors(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);

					IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsSettings, calculateColorsInfo.additionalDataToPassThrough);
				}
			}
		}
	}
}

void VertexPaintFunctions::RunPaintSetMeshColorsUsingSerializedStringCallbacks(const FCalculateColorsInfo& calculateColorsInfo) {


	if (IsValid(calculateColorsInfo.initiatedByComponent)) {

		if (calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings.callbackSettings.runCallbackDelegate)
			calculateColorsInfo.initiatedByComponent->vertexColorsSetMeshColorsUsingSerializedStringDelegate.Broadcast(calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings, calculateColorsInfo.additionalDataToPassThrough);
	}


	if (IsValid(calculateColorsInfo.vertexPaintActor)) {

		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_PaintedOnActor_SetMeshComponentVertexColorsUsingSerializedString(calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings.actor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings, calculateColorsInfo.additionalDataToPassThrough);


		// Calls interface on the painted actor so they can run custom things if they get painted on
		if (calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings.callbackSettings.runCallbackInterfaces && calculateColorsInfo.vertexPaintActor->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass()))
			IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(calculateColorsInfo.vertexPaintActor, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings, calculateColorsInfo.additionalDataToPassThrough);


		if (calculateColorsInfo.fundementalStruct.callbackSettings.runCallbackInterfacesOnChildComponents) {

			// Runs the Interface on any components as well if they're owner got it run, so you can't make cleaner implementations
			for (auto componentTemp : calculateColorsInfo.vertexPaintActor->GetComponents()) {

				if (componentTemp->GetClass()->ImplementsInterface(UVertexPaintDetectionInterface::StaticClass())) {

					IVertexPaintDetectionInterface::Execute_PaintedOnActor_SetMeshComponentVertexColorsUsingSerializedString(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings, calculateColorsInfo.additionalDataToPassThrough);

					IVertexPaintDetectionInterface::Execute_ColorsAppliedOnActor(componentTemp, calculateColorsInfo.taskResult, calculateColorsInfo.paintTaskResult, calculateColorsInfo.setMeshComponentVertexColorsUsingSerializedStringSettings, calculateColorsInfo.additionalDataToPassThrough);
				}
			}
		}
	}
}


//-------------------------------------------------------

// Check Valids

bool VertexPaintFunctions::CheckValidFundementals(FVertexDetectFundementalStruct taskFundementals, UPrimitiveComponent* component) {


	if (!IsValid(component)) {

		if (taskFundementals.debugSettings.printLogsToOutputLog)
			UE_LOG(LogTemp, Warning, TEXT("VertexPaint - Trying to Paint/Detect but Component provided is not Valid! Have you connected anything to the component pin on the Node?"));

		return false;
	}

	if (!IsWorldValid(component->GetWorld())) {

		if (taskFundementals.debugSettings.printLogsToOutputLog)
			UE_LOG(LogTemp, Warning, TEXT("VertexPaint - World not Valid"));

		return false;
	}

	if (!IsInGameThread()) {

		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Start a Task but not from Game Thread!")), FColor::Red);

		return false;
	}


	if (!IsValid(component->GetOwner()->GetLevel()->GetOuter())) {

		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Actor not in valid sub level!")), FColor::Red);

		return false;
	}

	UStaticMeshComponent* staticMeshComp_Local = nullptr;
	USkeletalMeshComponent* skelMeshComp_Local = nullptr;
	UInstancedStaticMeshComponent* instancedMeshComp_Local = nullptr;
	USkeletalMesh* skelMesh_Local = nullptr;

	staticMeshComp_Local = Cast<UStaticMeshComponent>(component);

	if (!staticMeshComp_Local) {

		skelMeshComp_Local = Cast<USkeletalMeshComponent>(component);
	}
	else {

		instancedMeshComp_Local = Cast<UInstancedStaticMeshComponent>(component);
	}



#if ENGINE_MAJOR_VERSION == 5

	UDynamicMeshComponent* dynamicMeshComp_Local = nullptr;
	UGeometryCollectionComponent* geometryCollectionComp_Local = nullptr;
	
	if (!staticMeshComp_Local && !skelMeshComp_Local) {

		dynamicMeshComp_Local = Cast<UDynamicMeshComponent>(component);
		
		if (!dynamicMeshComp_Local)
			geometryCollectionComp_Local = Cast<UGeometryCollectionComponent>(component);
	}


	if (!staticMeshComp_Local && !skelMeshComp_Local && !dynamicMeshComp_Local && !geometryCollectionComp_Local && !instancedMeshComp_Local) {

		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect but Component %s is not a Static, Spline, Skeletal, Dynamic, Instanced or Geometry Collection Mesh!"), *component->GetName()), FColor::Red);

		return false;
	}

#else

	if (!staticMeshComp_Local && !skelMeshComp_Local) {

		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect but Component %s is not a Static, Spline or Skeletal Mesh!"), *component->GetName()), FColor::Red);

		return false;
	}

#endif


	if (staticMeshComp_Local) {

		if (!IsValid(staticMeshComp_Local->GetStaticMesh())) {


			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Static Mesh Component %s but it has no Mesh is Set"), *staticMeshComp_Local->GetName()), FColor::Red);

			return false;
		}

		if (!staticMeshComp_Local->GetStaticMesh()->bAllowCPUAccess) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Static Mesh but it's CPU Access is not set to True")), FColor::Red);

			return false;
		}


#if ENGINE_MAJOR_VERSION == 5

		// Note ->NaniteSettings was only available in Editor, so had to use this to check if nanite is enabled. 
		if (staticMeshComp_Local->GetStaticMesh().Get()->HasValidNaniteData()) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Static Mesh that has Nanite Enabled! Vertex Painting on Nanite Meshes is currently not supported. ")), FColor::Red);

			return false;
		}

#endif


		if (!staticMeshComp_Local->GetBodySetup()) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Static Mesh but it doesn't have a Body Setup")), FColor::Red);

			return false;
		}


		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Static Mesh Component, with Source Mesh: %s"), *staticMeshComp_Local->GetStaticMesh()->GetName()), FColor::Cyan);
	}

	else if (skelMeshComp_Local) {


#if ENGINE_MAJOR_VERSION == 4

		skelMesh_Local = skelMeshComp_Local->SkeletalMesh;

#elif ENGINE_MAJOR_VERSION == 5

#if ENGINE_MINOR_VERSION == 0

		skelMesh_Local = skelMeshComp_Local->SkeletalMesh.Get();

#else

		skelMesh_Local = skelMeshComp_Local->GetSkeletalMeshAsset();

#endif
#endif


		if (!IsValid(skelMesh_Local)) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh Component but source mesh is null")), FColor::Red);

			return false;
		}

		else {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh Component, with Source Mesh: %s"), *skelMesh_Local->GetName()), FColor::Cyan);
		}


		if (!skelMeshComp_Local->GetSkeletalMeshRenderData()) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh but it hasn't properly been initialized yet because it's Skeletal Mesh Render Data isn't valid. ")), FColor::Red);

			return false;
		}

		if (!skelMeshComp_Local->GetSkeletalMeshRenderData()->IsInitialized()) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh %s but it's SkeletalMeshRenderData isn't Initialized yet. "), *component->GetOwner()->GetName()), FColor::Red);

			return false;
		}


		if (!skelMesh_Local->GetResourceForRendering()) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh %s but it has invalid ResourceForRendering!"), *component->GetOwner()->GetName()), FColor::Red);

			return false;
		}


		// Could get a crash very rarely if switching skeletal meshes and painting every frame, so added these for extra checks so we hopefully can't create a task if these aren't valid. We also have these in the task itself in case they become invalid after this. 
		for (int currentLOD_Local = 0; currentLOD_Local < skelMeshComp_Local->GetSkeletalMeshRenderData()->LODRenderData.Num(); currentLOD_Local++) {


			const FSkeletalMeshLODRenderData& skelMeshRenderData_Local = skelMeshComp_Local->GetSkeletalMeshRenderData()->LODRenderData[currentLOD_Local];

			if (skelMeshRenderData_Local.HasClothData()) {

				if (!skelMeshRenderData_Local.ClothVertexBuffer.IsInitialized()) {

					VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh with Cloth but cloth vertex buffer hasn't properly been initialized yet, i.e. the paint job is run to early. ")), FColor::Red);

					return false;
				}
			}

			if (!skelMeshRenderData_Local.StaticVertexBuffers.StaticMeshVertexBuffer.IsInitialized() || !skelMeshRenderData_Local.StaticVertexBuffers.StaticMeshVertexBuffer.TangentsVertexBuffer.IsInitialized() || !skelMeshRenderData_Local.StaticVertexBuffers.StaticMeshVertexBuffer.GetTangentData()) {

				VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Skeletal Mesh but it hasn't properly been initialized yet, i.e. the paint job is run to early. ")), FColor::Red);

				return false;
			}
		}
	}

	else if (instancedMeshComp_Local) {

		if (taskFundementals.componentItem < 0) {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Instanced Mesh %s but the Item provided is less than 0, so we can't get the specific instance and can calculate location properly. "), *instancedMeshComp_Local->GetName()), FColor::Red);

			return false;
		}
	}

#if ENGINE_MAJOR_VERSION == 5

	else if (dynamicMeshComp_Local) {

		if (dynamicMeshComp_Local->GetDynamicMesh()) {


			UE::Geometry::FDynamicMesh3* dynamicMesh3 = nullptr;
			dynamicMesh3 = &dynamicMeshComp_Local->GetDynamicMesh()->GetMeshRef();

			if (dynamicMesh3) {

				// Enable Vertex Colors so we can get them when running paint / Detect jobs
				if (!dynamicMesh3->HasVertexColors()) {

					dynamicMesh3->EnableVertexColors(FVector3f(0, 0, 0));
				}

				/*
				* If we Enable Normals and UVs, we apparently Set them to be whatever the initial value we give here as well, which may mess up something that the user want to have depending on the shape they've made. Think this is meant to be set somewhere where the dynamic mesh is being created, and if set correct there, the HasUVs and HasVertexNormals should be true and we should be able to get them later .
				*
				if (!dynamicMeshComp_Local->GetDynamicMesh()->GetMeshPtr()->HasVertexUVs())
					dynamicMeshComp_Local->GetDynamicMesh()->GetMeshPtr()->EnableVertexUVs(FVector2f(0, 1));

				if (!dynamicMeshComp_Local->GetDynamicMesh()->GetMeshPtr()->HasVertexNormals())
					dynamicMeshComp_Local->GetDynamicMesh()->GetMeshPtr()->EnableVertexNormals(FVector3f(0, 0, 1));
				*/

				VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Dynamic Mesh Component: %s"), *dynamicMeshComp_Local->GetName()), FColor::Cyan);
			}

			else {

				VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Dynamic Mesh Component: %s but DynamicMesh Object GetMeshPtr is null. "), *dynamicMeshComp_Local->GetName()), FColor::Red);

				return false;
			}
		}

		else {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Dynamic Mesh Component: %s but couldn't GetDynamicMesh Object. "), *dynamicMeshComp_Local->GetName()), FColor::Red);

			return false;
		}
	}

	else if (geometryCollectionComp_Local) {


		// Geometry Collection RebuildRenderData is only available from 5.3 so any version before that unfortunately can't paint on Geometry Collection Components. 

#if WITH_EDITOR



#if ENGINE_MINOR_VERSION >= 3

		if (geometryCollectionComp_Local->GetRestCollection()) {

			TSharedPtr<FGeometryCollection, ESPMode::ThreadSafe> geometryCollectionData = geometryCollectionComp_Local->GetRestCollection()->GetGeometryCollection();


			if (geometryCollectionData.Get()) {

				VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Geometry Collection Component with Rest Collection: %s"), *geometryCollectionComp_Local->GetRestCollection()->GetName()), FColor::Cyan);
			}

			else {

				VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Geometry Collection Component Geometry Collection Data isn't valid!")), FColor::Red);
			}
		}

		else {

			VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Geometry Collection Component but couldn't get Rest Collection!")), FColor::Red);
		}

#else

		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Geometry Collection Component but Engine Version is not 5.3 or up!")), FColor::Red);

		return false;

#endif

#else

		VertexPaintFunctions::PrintTaskLog(taskFundementals.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint/Detect on Geometry Collection Component but Not in Editor Time. You can currently only paint on them in Editor since the GeometryCollection->RebuildRenderData is Editor Only!")), FColor::Red);

		return false;

#endif

	}
#endif 

	return true;
}


bool VertexPaintFunctions::CheckValidVertexPaintSettings(FVertexPaintStruct vertexPaintSettings) {

	if (!IsValid(vertexPaintSettings.actor)) return false;
	if (!IsValid(vertexPaintSettings.actor->GetWorld())) return false;
	if (!IsValid(vertexPaintSettings.meshComponent)) return false;


	// Can ignore the task queue limit, in case you need to load a game and queue a bunch of paint task but just once
	if (!vertexPaintSettings.ignoreTaskQueueLimit) {

		int maxAllowedTasks_Local = GetDefault<UVertexPaintDetectionSettings>()->VertexPaintFunctionsLib_MaxAmountOfAllowedTasksPerMesh;
		int taskAmount_Local = 0;

		if (GetVertexPaintTaskQueue(vertexPaintSettings.meshComponent))
			taskAmount_Local = GetVertexPaintTaskQueue(vertexPaintSettings.meshComponent)->GetAmountOfPaintTasksComponentHas(vertexPaintSettings.meshComponent);

		if (taskAmount_Local >= maxAllowedTasks_Local) {

			// Always prints this to log so users can see in the output that something may not be fully optimized
			UKismetSystemLibrary::PrintString(vertexPaintSettings.actor->GetWorld(), FString::Printf(TEXT("VertexPaint - Mesh: %s Has over %i Allowed Paint Tasks Queue Limit and we don't Allow any more per Mesh as the Performance gets affected if the queue per mesh becomes too big since the TMaps become more expensive to use! You can change this in the Project Settings, but if the queue grows to big you will get unwanted result as well since it may take a while for a paint job to show it's effect. \nRecommend Reviewing how often you Add new Tasks. You can for instance Add a New Task when the Old one is Finished instead of adding them every frame. "), *vertexPaintSettings.meshComponent->GetName(), maxAllowedTasks_Local), vertexPaintSettings.debugSettings.printLogsToScreen, true, FColor::Red, vertexPaintSettings.debugSettings.printLogsToScreen_Duration);

			return false;
		}
	}


	if (vertexPaintSettings.overrideLOD.overrideLODToPaintUpTo) {

		if (vertexPaintSettings.overrideLOD.amountOfLODsToPaint <= 0) {

			VertexPaintFunctions::PrintTaskLog(vertexPaintSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint and Override LOD to paint on but LOD given is <= 0!")), FColor::Red);

			return false;
		}
	}


	// If anything is added onto the array
	if (vertexPaintSettings.canOnlyApplyPaintOnTheseActors.Num() > 0) {

		// If the actor we're trying to paint on isn't in the array. 
		if (!vertexPaintSettings.canOnlyApplyPaintOnTheseActors.Contains(vertexPaintSettings.actor)) {

			VertexPaintFunctions::PrintTaskLog(vertexPaintSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Actor: %s  isn't in the canOnlyApplyPaintOnTheseActors array that has been set. Either add the actor to it, or don't fill the array."), *vertexPaintSettings.actor->GetName()), FColor::Red);

			return false;
		}
	}


	if (auto skelMeshComp = Cast<USkeletalMeshComponent>(vertexPaintSettings.meshComponent)) {

		if (skelMeshComp->GetSkeletalMeshRenderData()) {

			if (skelMeshComp->GetSkeletalMeshRenderData()->LODRenderData.IsValidIndex(skelMeshComp->GetPredictedLODLevel())) {

				// If current viewable LOD has cloth then requires bWaitForParallelClothTask to be true
				if (skelMeshComp->GetSkeletalMeshRenderData()->LODRenderData[skelMeshComp->GetPredictedLODLevel()].HasClothData()) {

					if (!skelMeshComp->bWaitForParallelClothTask && vertexPaintSettings.affectClothPhysics) {

						VertexPaintFunctions::PrintTaskLog(vertexPaintSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Detect/Paint on Skeletal Mesh with Cloth, with affectClothPhysics to True but the Skeletal Mesh Component bWaitForParallelClothTask is false! You can set it to True by selecting the skeletal mesh component and set bWaitForParallelClothTask to True in the Details. ")), FColor::Red);

						return false;
					}
				}
			}
		}
	}


	if (vertexPaintSettings.overrideVertexColorsToApplySettings.overrideVertexColorsToApply && !(IsValid(vertexPaintSettings.overrideVertexColorsToApplySettings.actorToRunOverrideVertexColorsInterface) || IsValid(vertexPaintSettings.overrideVertexColorsToApplySettings.componentToRunOverrideVertexColorsInterface))) {

		VertexPaintFunctions::PrintTaskLog(vertexPaintSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Paint and Override Vertex Colors To Apply, but the neither the Actor or Component set to run the Override Vertex Colors Interface is valid! Task will still run but the interface won't be called. ")), FColor::Orange);
	}

	return true;
}


bool VertexPaintFunctions::CheckValidVertexPaintColorSettings(FVertexPaintColorSettingStruct colorSettings) {

	if (!IsValid(colorSettings.actor)) return false;
	if (!IsValid(colorSettings.actor->GetWorld())) return false;
	if (!IsValid(colorSettings.meshComponent)) return false;

	bool applyUsingPhysicsSurface_GotColorsToApplyOnMaterial = false;


	if (colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyVertexColorUsingPhysicsSurface) {


		if (!GetVertexPaintMaterialDataAsset(colorSettings.meshComponent)) {

			VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surface, but no Material Data Asset is set in the Project Settings. This means that we can't get what Physics Surface is on each Vertex Color Channel. ")), FColor::Red);

			return false;
		}


		// If set to paint with Physics Surface with Add, but the Paint Strength is 0 so no difference will be made
		if (colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply == 0 && colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface == 0 && colorSettings.applyVertexColorSettings.applyVertexColorSetting == EApplyVertexColorSetting::EAddVertexColor) {


			if (colorSettings.overrideVertexColorsToApplySettings.overrideVertexColorsToApply && (IsValid(colorSettings.overrideVertexColorsToApplySettings.actorToRunOverrideVertexColorsInterface) || IsValid(colorSettings.overrideVertexColorsToApplySettings.componentToRunOverrideVertexColorsInterface))) {

				VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surface, but with Paint Strength 0. But since the task is also set to Override Vertex Colors, the task will be allowed to run. ")), FColor::Orange);
			}

			else {

				VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surface, but Paint Strength Multiplier is 0. ")), FColor::Red);

				return false;
			}
		}


		if (colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.physicsSurfacesToApply.Num() <= 0) {

			VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surface, but no Physics Surfaces has been added to the Array. ")), FColor::Red);

			return false;
		}

		bool validPhysicsSurfaceToApply_Local = true;

		for (auto physicsSurfaceTemp : colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.physicsSurfacesToApply) {

			if (physicsSurfaceTemp == EPhysicalSurface::SurfaceType_Default) {

				validPhysicsSurfaceToApply_Local = false;
				break;
			}
		}

		if (!validPhysicsSurfaceToApply_Local) {

			VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surfaces, but one of them set to apply Default Physics Surface which isn't possible. ")), FColor::Red);

			return false;
		}


		for (int i = 0; i < colorSettings.meshComponent->GetNumMaterials(); i++) {

			for (auto physicsSurfaceToApplyTemp : colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.physicsSurfacesToApply) {

				float redColorToApplyTemp = 0;
				float greenColorToApplyTemp = 0;
				float blueColorToApplyTemp = 0;
				float alphaColorToApplyTemp = 0;

				bool redColorToApplySuccessfullyGotTemp = false;
				bool greenColorToApplySuccessfullyGotTemp = false;
				bool blueColorToApplySuccessfullyGotTemp = false;
				bool alphaColorToApplySuccessfullyGotTemp = false;

				bool successfullyGotVertexColorsToApplyTemp = false;

				VertexPaintFunctions::GetColorsToApplyFromPhysicsSurface_Wrapper(colorSettings.meshComponent, colorSettings.meshComponent->GetMaterial(i), physicsSurfaceToApplyTemp, redColorToApplyTemp, redColorToApplySuccessfullyGotTemp, greenColorToApplyTemp, greenColorToApplySuccessfullyGotTemp, blueColorToApplyTemp, blueColorToApplySuccessfullyGotTemp, alphaColorToApplyTemp, alphaColorToApplySuccessfullyGotTemp, successfullyGotVertexColorsToApplyTemp, colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengthToApply, colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.paintStrengtOnChannelsWithoutThePhysicsSurface, colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyOnChannelsThatIsAParentOfPhysicsSurface, colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyOnChannelsThatsChildOfPhysicsSurface, colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyOnChannelsThatResultsInBlendableSurfaces);


				if (successfullyGotVertexColorsToApplyTemp) {

					applyUsingPhysicsSurface_GotColorsToApplyOnMaterial = true;
					break;
				}
			}

			if (applyUsingPhysicsSurface_GotColorsToApplyOnMaterial)
				break;
		}

		if (!applyUsingPhysicsSurface_GotColorsToApplyOnMaterial) {

			if (colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.fallbackToRGBAColorsIfFailedToApplyColorsUsingPhysicsSurface) {

				VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surface, but was unable to get Colors To Apply on any of the Mesh's Materials. Double check if the physics surfaces is registered to it, as well as physics surface families is setup correctly. Is set to Fallback to RGBA Colors so will check if those will make a difference.")), FColor::Orange);
			}
			else {

				VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Set to Apply Colors Using Physics Surface, but was unable to get Colors To Apply on any of the Mesh's Materials, and is set to Not fallback to the RGBA Colors. Double check if the physics surfaces is registered to it, as well as physics surface families is setup correctly. ")), FColor::Red);

				return false;
			}
		}
	}

	// If set to paint with Add then check if any difference is going to be made, either by painting regularly, or with Apply using Physics Surface if it's true, but set to fallback to RGBA colors and wasn't able to get colors to apply using physics surface
	if (colorSettings.applyVertexColorSettings.applyVertexColorSetting == EApplyVertexColorSetting::EAddVertexColor && (!colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyVertexColorUsingPhysicsSurface || (colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.applyVertexColorUsingPhysicsSurface && colorSettings.applyVertexColorSettings.applyColorsUsingPhysicsSurface.fallbackToRGBAColorsIfFailedToApplyColorsUsingPhysicsSurface && !applyUsingPhysicsSurface_GotColorsToApplyOnMaterial))) {

		// If all apply color is 0
		if (colorSettings.applyVertexColorSettings.redColor == 0 && colorSettings.applyVertexColorSettings.greenColor == 0 && colorSettings.applyVertexColorSettings.blueColor == 0 && colorSettings.applyVertexColorSettings.alphaColor == 0) {


			if (colorSettings.overrideVertexColorsToApplySettings.overrideVertexColorsToApply && (IsValid(colorSettings.overrideVertexColorsToApplySettings.actorToRunOverrideVertexColorsInterface) || IsValid(colorSettings.overrideVertexColorsToApplySettings.componentToRunOverrideVertexColorsInterface))) {

				VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Apply Colors with RGBA with 0 Strength in Colors. But since the Task is also set to Override Vertex Colors, it will be allowed to run. ")), FColor::Orange);
			}

			else {

				VertexPaintFunctions::PrintTaskLog(colorSettings.debugSettings, FString::Printf(TEXT("VertexPaint - Trying to Apply Colors with RGBA with 0 Strength in Colors which wouldn't make any difference. ")), FColor::Red);

				return false;
			}
		}
	}


	return true;
}


bool VertexPaintFunctions::CheckHaveReachedMaxDetectionTask(FVertexDetectFundementalStruct fundementalSettings) {

	if (!IsValid(fundementalSettings.actor)) return false;
	if (!IsValid(fundementalSettings.actor->GetWorld())) return false;
	if (!IsValid(fundementalSettings.meshComponent)) return false;


	// Can ignore the Task queue limit, which may be useful for Save / Load Systems, in case you need to detect on a bunch of meshes but just once
	if (!fundementalSettings.ignoreTaskQueueLimit) {

		int maxAllowedTasks_Local = GetDefault<UVertexPaintDetectionSettings>()->VertexPaintFunctionsLib_MaxAmountOfAllowedTasksPerMesh;
		int taskAmount_Local = 0;

		if (GetVertexPaintTaskQueue(fundementalSettings.meshComponent))
			taskAmount_Local = GetVertexPaintTaskQueue(fundementalSettings.meshComponent)->GetAmountOfDetectionTasksComponentHas(fundementalSettings.meshComponent);

		if (taskAmount_Local >= maxAllowedTasks_Local) {

			// Always prints this to log so users can see in the output that something may not be fully optimized
			UKismetSystemLibrary::PrintString(fundementalSettings.meshComponent->GetWorld(), FString::Printf(TEXT("VertexPaint - Mesh: %s Has over %i Allowed Detect Tasks Queue Limit and we don't Allow any more per Mesh as the Performance gets affected if the queue per mesh becomes to big since the TMaps become more expensive to use! You can change this in the Project Settings, but if the queue grows too big you will get unwanted result as well since it may take a while for a detect job run and the callback will run. \nRecommend Reviewing how often you Add new Tasks. You can for instance Add a New Task when the Old one is Finished instead of adding them every frame. "), *fundementalSettings.meshComponent->GetName(), maxAllowedTasks_Local), fundementalSettings.debugSettings.printLogsToScreen, true, FColor::Red, fundementalSettings.debugSettings.printLogsToScreen_Duration);

			return true;
		}
	}

	else {

		return false;
	}


	return false;
}
