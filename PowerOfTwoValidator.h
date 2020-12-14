// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetActionUtility.h"
#include "PowerOfTwoValidator.generated.h"

/**
 * 
 */
UCLASS()
class PWR_OF_TWO_VALIDATOR_API UPowerOfTwoValidator : public UAssetActionUtility
{
	GENERATED_BODY()

public:

	/**
	* Function to determine if a texture is of size power of two.
	* Why is this something that should be done? It is important that a texture should be of a size power of two to make more efficient use of memory.
	* When an object-whether it is a texture or something else- is loaded from source into memory, it is loaded 2^N bytes at a time, where N is equal to the
	* number of bits in the memory address bus.
	* 
	* The minimum number of reads from source into the memory address is (X/(2^N)), where X is the size of the object in bytes. If X is an exact power of two,
	* the object will be read completely in ((2^M)/(2^N)) times, where M is the number of bits required to store the object.
	* 
	* If the data size is NOT a power of twp, there will be extra reads from source to get all the data into memory. This will result in more operations necessary
	* to completely read the data into memory, which will result in a slower application, especially on mobile devices.
	**/
	UFUNCTION(CallInEditor)
	void CheckPowerOfTwo();

private:

	bool IsPowerOfTwo(int32 num);

	/**
	* Function to print message to screen. (TODO: combine with larger UE utility package being created)
	* @param message - The message to print
	* @param color - The color to print the message text in
	**/
	void PrintToScreen(FString message, FColor color);

	/**
	* Function to give feedback to user informing them of how many items have been affected/determined by the utility. (TODO: combine with larger UE utility package being created)
	* @param message - The message to print
	* @param color - The color to print the message text in
	**/
	void GiveFeedback(FString methodName, uint32 affectedCount);
	
};
