// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"

int32 AMyActor::step()
{
	// �õ� ���� -> Begin����
	//FMath::RandInit(FDateTime::Now().GetMillisecond());

	// ���� �� ��ȯ	
	return FMath::RandRange(0, 1);
}

FVector AMyActor::MoveCharacter(FVector Movement)
{


	if (PlayerCharacter)
	{
		// ������ ĳ������ ���� ��ġ�� GetActorLocatino �Լ��� ��ȯ�ؼ� �����Ѵ�.
		FVector CurrentLocation = PlayerCharacter->GetActorLocation();

		// ���ο� ��ġ ���
		FVector NewLocation = CurrentLocation + Movement;

		// ĳ������ ���ο� ��ġ ����
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
		// �÷��̾� ĳ���� ���� -> ���� ��ġ ��������
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
	// ���� BeginPlay() �Լ����� �� ���� �÷��̾� ĳ���͸� �������� �ȴ�.
	PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (!PlayerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("No player character found"));
	}

	// �õ带 �� ���� �ʱ�ȭ
	FMath::RandInit(FDateTime::Now().GetMillisecond());
		
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	static float AccumulatedTime = 0.0f; // ���� �ð�
	static int32 Count = 0; // �̵� Ƚ��
	static int32 event_count = 0; // �̺�Ʈ �߻� Ƚ��

	AccumulatedTime += DeltaTime; // DeltaTime ����

	if (AccumulatedTime >= 1.0f) // 1�ʰ� ������ �� ����
	{
		AccumulatedTime = 0.0f; // �ð� �ʱ�ȭ


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
			// �Ÿ� ���ϱ� �߰�
			float one_distance = Distance(FVector(0, 0, 0), Movement);
			UE_LOG(LogTemp, Warning, TEXT("Move distance: %f"), one_distance);
			
			// ��ġ ���
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

