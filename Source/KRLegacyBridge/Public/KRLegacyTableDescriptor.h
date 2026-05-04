#pragma once

#include "KRLegacyTableDescriptor.generated.h"

UENUM(BlueprintType)
enum class EKRLegacyTablePriority : uint8
{
    Critical,
    Recommended,
    Deferred
};

USTRUCT(BlueprintType)
struct KRLEGACYBRIDGE_API FKRLegacyTableDescriptor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Legacy")
    FString LogicalName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Legacy")
    FString SourceRelativePath;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Legacy")
    FString Notes;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Legacy")
    EKRLegacyTablePriority Priority = EKRLegacyTablePriority::Critical;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Legacy")
    TArray<FString> ExpectedSheetNames;
};
