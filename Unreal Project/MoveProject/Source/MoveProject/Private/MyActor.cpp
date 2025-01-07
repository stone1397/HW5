// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"

int32 AMyActor::step()
{
	// �õ� ����
	//FMath::RandInit(FDateTime::Now().GetMillisecond());

	// ���� �� ��ȯ	
	return FMath::RandRange(0, 1);
}

void AMyActor::MoveCharacter(FVector Movement)
{
	//���� �÷��̾� ĳ���� ���� �������� 
	ACharacter* PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (PlayerCharacter)
	{
		// ������ ĳ������ ���� ��ġ�� GetActorLocatino �Լ��� ��ȯ�ؼ� �����Ѵ�.
		FVector CurrentLocation = PlayerCharacter->GetActorLocation();

		// ���ο� ��ġ ���
		FVector NewLocation = CurrentLocation + Movement;

		// ĳ������ ���ο� ��ġ ����
		PlayerCharacter->SetActorLocation(NewLocation);

		// ĳ������ ��ġ ���
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
	
	// �õ带 �� ���� �ʱ�ȭ
	FMath::RandInit(FDateTime::Now().GetMillisecond());
		
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	static float AccumulatedTime = 0.0f; // ���� �ð�
	static int32 Count = 0; // �̺�Ʈ Ƚ��

	AccumulatedTime += DeltaTime; // DeltaTime ����

	if (AccumulatedTime >= 1.0f) // 1�ʰ� ������ �� ����
	{
		AccumulatedTime = 0.0f; // �ð� �ʱ�ȭ

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

