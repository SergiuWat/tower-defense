// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM(BlueprintType)
enum class ELocomotionDirections : uint8
{
	ELD_Forward UMETA(DisplayName = "Forward"),
	ELD_Backward UMETA(DisplayName = "Backward"),
	ELD_Left UMETA(DisplayName = "Left"),
	ELD_Right UMETA(DisplayName = "Right"),

	ELD_MAX UMETA(DisplayName = "DefaultMAX")
};