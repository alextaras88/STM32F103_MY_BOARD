#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>


// ����� ������������, 6�8 ��������
#define f6x8_MONO_WIDTH         6
#define f6x8_MONO_HEIGHT        8

// ���-�� �������� � ������� ������
#define f6x8m_NOFCHARS           256


// ������� ���������� ��������� �� ���������� ������� Char
uint8_t *f6x8m_GetCharTable(uint8_t Char);


