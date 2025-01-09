// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"

int32 AMyActor::step()
{
	// 시드 설정 -> Begin에서
	//FMath::RandInit(FDateTime::Now().GetMillisecond());

	// 랜덤 값 반환	
	return FMath::RandRange(0, 1);
}

FVector AMyActor::MoveCharacter(FVector Movement)
{


	if (PlayerCharacter)
	{
		// 가져온 캐릭터의 현재 위치를 GetActorLocatino 함수로 반환해서 저장한다.
		FVector CurrentLocation = PlayerCharacter->GetActorLocation();

		// 새로운 위치 계산
		FVector NewLocation = CurrentLocation + Movement;

		// 캐릭터의 새로운 위치 설정
		PlayerCharacter->SetActorLocation(NewLocation);

		return NewLocation;
	}

	UE_LOG(LogTemp, Warning, TEXT("No player character found"));
	return FVector(0, 0, 0);

	
}

void AMyActor::displayPosition(int32 X, int32 Y)
{
	if (PlayerCharacter)
	{
		// 플레이어 캐릭터 존재 -> 현재 위치 가져오기
		FVector CurrentLocation = PlayerCharacter->GetActorLocation();

		UE_LOG(LogTemp, Warning, TEXT("Current Character Location: (%f, %f, %f)"), CurrentLocation.X, CurrentLocation.Y, CurrentLocation.Z);
		UE_LOG(LogTemp, Warning, TEXT("Step Position (X, Y): (%d, %d)"), X, Y);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No player character found"));
	}
}

float AMyActor::Distance(const FVector& Start, const FVector& End)
{
	float dx = End.X - Start.X;
	float dy = End.Y - Start.Y;
	return FMath::Sqrt(dx * dx + dy * dy);
}

void AMyActor::Notify(int32 EventCount, float SumDistance)
{
	UE_LOG(LogTemp, Warning, TEXT("Event count: %d"), EventCount);
    UE_LOG(LogTemp, Warning, TEXT("Sum of Distance: %f"), SumDistance);
}

int32 AMyActor::createEvent()
{
	int32 probability = FMath::RandRange(0, 100);
	int32 count = 0;
	if (probability >= 50)
	{
		UE_LOG(LogTemp, Warning, TEXT("Event occurred!"));
		count++;
	}
	
	return count;
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
	// 이젠 BeginPlay() 함수에서 한 번만 플레이어 캐릭터를 가져오면 된다.
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player character found"));
	}

	// 시드를 한 번만 초기화
	FMath::RandInit(FDateTime::Now().GetMillisecond());
		
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	static float AccumulatedTime = 0.0f; // 누적 시간
	static int32 Count = 0; // 이동 횟수
	static int32 event_count = 0; // 이벤트 발생 횟수

	AccumulatedTime += DeltaTime; // DeltaTime 누적

	if (AccumulatedTime >= 1.0f) // 1초가 지났을 때 실행
	{
		AccumulatedTime = 0.0f; // 시간 초기화


		if (Count < 10)
		{
			int32 X = step();
			int32 Y = step();
			FVector Movement = FVector(X, Y, 0);
			
			
			
		//	int32 event_count = createEvent();
		//	UE_LOG(LogTemp, Warning, TEXT("Event count: %d"), event_count);
			if (createEvent())
			{
				event_count++;
			}

			FVector current_pos = MoveCharacter(Movement);
			// 거리 구하기 추가
			float one_distance = Distance(FVector(0, 0, 0), Movement);
			UE_LOG(LogTemp, Warning, TEXT("Move distance: %f"), one_distance);
			
			// 위치 출력
			displayPosition(X, Y);

			Count++;

			if (Count == 10)
			{

				float sum_distance = Distance(FVector(0, 0, 0), current_pos);
				Notify(event_count, sum_distance);

			}

			//UE_LOG(LogTemp, Warning, TEXT("Step %d: X=%d, Y=%d"), Count, X, Y);
		}
	}
}

