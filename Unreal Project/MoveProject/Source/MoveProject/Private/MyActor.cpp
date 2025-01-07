// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"

int32 AMyActor::step()
{
	// 시드 설정
	//FMath::RandInit(FDateTime::Now().GetMillisecond());

	// 랜덤 값 반환	
	return FMath::RandRange(0, 1);
}

void AMyActor::MoveCharacter(FVector Movement)
{
	//현재 플레이어 캐릭터 참조 가져오기 
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter)
	{
		// 가져온 캐릭터의 현재 위치를 GetActorLocatino 함수로 반환해서 저장한다.
		FVector CurrentLocation = PlayerCharacter->GetActorLocation();

		// 새로운 위치 계산
		FVector NewLocation = CurrentLocation + Movement;

		// 캐릭터의 새로운 위치 설정
		PlayerCharacter->SetActorLocation(NewLocation);

		// 캐릭터의 위치 출력
		UE_LOG(LogTemp, Warning, TEXT("New Character Location: (%f, %f, %f)"), NewLocation.X, NewLocation.Y, NewLocation.Z);
	}

}



// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
	// 시드를 한 번만 초기화
	FMath::RandInit(FDateTime::Now().GetMillisecond());
		
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	static float AccumulatedTime = 0.0f; // 누적 시간
	static int32 Count = 0; // 이벤트 횟수

	AccumulatedTime += DeltaTime; // DeltaTime 누적

	if (AccumulatedTime >= 1.0f) // 1초가 지났을 때 실행
	{
		AccumulatedTime = 0.0f; // 시간 초기화

		if (Count <= 10)
		{
			int32 X = step();
			int32 Y = step();
			FVector Movement = FVector(X, Y, 0);
			UE_LOG(LogTemp, Warning, TEXT("(X, Y): (%d, %d)"), X, Y);

			MoveCharacter(Movement);
			Count++;

			//UE_LOG(LogTemp, Warning, TEXT("Step %d: X=%d, Y=%d"), Count, X, Y);
		}
	}
}

