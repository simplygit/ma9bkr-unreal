#pragma once

#include "GameFramework/GameStateBase.h"

#include "KRPrototypeMatchTypes.h"
#include "KRPrototypeGameState.generated.h"

UCLASS()
class KRGAMEPLAY_API AKRPrototypeGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    AKRPrototypeGameState();

    UFUNCTION(BlueprintCallable, Category="Prototype Match")
    void StartPrototypeMatch();

    UFUNCTION(BlueprintCallable, Category="Prototype Match")
    void RecordOut();

    UFUNCTION(BlueprintCallable, Category="Prototype Match")
    void AddRun(bool bHomeTeamScored);

    UFUNCTION(BlueprintPure, Category="Prototype Match")
    const FKRPrototypeMatchState& GetMatchState() const;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Prototype Match")
    FKRPrototypeMatchState MatchState;

private:
    void AdvanceHalfInningIfNeeded();
};
