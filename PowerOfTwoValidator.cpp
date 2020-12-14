// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerOfTwoValidator.h"
#include "EditorUtilityLibrary.h"
#include "Engine/Texture.h"

#pragma region CheckPowerOfTwo

void UPowerOfTwoValidator::CheckPowerOfTwo()
{
	//Get all selected assets
	TArray<UObject*> SelectedObjects = UEditorUtilityLibrary::GetSelectedAssets();

	//A count for the number of files that are a power of two in size.
	uint32 counter = 0;

	//For each valid selected object, obtain the texture
	for (UObject* SelectedObject : SelectedObjects)
	{
		if (ensure(SelectedObject))
		{
			UTexture* texture = dynamic_cast<UTexture*>(SelectedObject);

			//Is texture a valid pointer?
			if (ensure(texture))
			{

				//Obtain width and height of texture if so.
				int32 Width = static_cast<int32>(texture->GetSurfaceWidth());
				int32 Height = static_cast<int32>(texture->GetSurfaceHeight());

				//Check if the width and height of each image is a power of two. If either is not, the texture fails the test (is not a power of two in size)
				if (!IsPowerOfTwo(Width) || !IsPowerOfTwo(Height))
				{
					PrintToScreen(SelectedObject->GetPathName() + " is not a power of 2 texture.", FColor::Red);
				}
				else
				{
					++counter;
				}
			}
			else
			{
				PrintToScreen(SelectedObject->GetPathName() + " is not a texture.", FColor::Red);
			}
		}
	}

	GiveFeedback("Power of Two", counter);
}

bool UPowerOfTwoValidator::IsPowerOfTwo(int32 num)
{
	//If the number is zero, immediately return false: if the exponent is zero, the value would be one, which is not a power of two.
	if (num == 0)
	{
		return false;
	}

	//If the bitwise and of the number to check and the number to check minus one is zero, we have a power of two.
	return ((num & (num - 1)) == 0);
}

void UPowerOfTwoValidator::PrintToScreen(FString message, FColor color)
{
	//Check first that the engine is up before calling.
	if (ensure(GEngine))
	{
		//Display message for 2.5 seconds in chosen color. TODO: consider adding parameter that takes in the number of seconds for display.
		GEngine->AddOnScreenDebugMessage(-1, 2.5, color, message);
	}
}

void UPowerOfTwoValidator::GiveFeedback(FString methodName, uint32 affectedCount)
{
	//Create a default message to return.
	FString msg = FString("No matching files found.");
	FColor color = affectedCount > 0 ? FColor::Green : FColor::Red;
	if (affectedCount > 0)
	{
		msg = methodName.AppendChar(' ');
		msg.AppendInt(affectedCount);
		msg.Append(affectedCount == 1 ? TEXT(" file") : TEXT(" files"));
	}
	PrintToScreen(msg, color);
}

#pragma endregion

