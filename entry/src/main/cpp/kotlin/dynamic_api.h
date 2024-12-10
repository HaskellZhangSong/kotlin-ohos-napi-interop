#ifndef KONAN_DYNAMIC_H
#define KONAN_DYNAMIC_H
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
typedef bool            dynamic_KBoolean;
#else
typedef _Bool           dynamic_KBoolean;
#endif
typedef unsigned short     dynamic_KChar;
typedef signed char        dynamic_KByte;
typedef short              dynamic_KShort;
typedef int                dynamic_KInt;
typedef long long          dynamic_KLong;
typedef unsigned char      dynamic_KUByte;
typedef unsigned short     dynamic_KUShort;
typedef unsigned int       dynamic_KUInt;
typedef unsigned long long dynamic_KULong;
typedef float              dynamic_KFloat;
typedef double             dynamic_KDouble;
typedef float __attribute__ ((__vector_size__ (16))) dynamic_KVector128;
typedef void*              dynamic_KNativePtr;
struct dynamic_KType;
typedef struct dynamic_KType dynamic_KType;

typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Byte;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Short;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Int;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Long;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Float;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Double;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Char;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Boolean;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_Unit;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_UByte;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_UShort;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_UInt;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_kotlin_ULong;
typedef struct {
  dynamic_KNativePtr pinned;
} dynamic_kref_KNObject;


typedef struct {
  /* Service functions. */
  void (*DisposeStablePointer)(dynamic_KNativePtr ptr);
  void (*DisposeString)(const char* string);
  dynamic_KBoolean (*IsInstance)(dynamic_KNativePtr ref, const dynamic_KType* type);
  dynamic_kref_kotlin_Byte (*createNullableByte)(dynamic_KByte);
  dynamic_KByte (*getNonNullValueOfByte)(dynamic_kref_kotlin_Byte);
  dynamic_kref_kotlin_Short (*createNullableShort)(dynamic_KShort);
  dynamic_KShort (*getNonNullValueOfShort)(dynamic_kref_kotlin_Short);
  dynamic_kref_kotlin_Int (*createNullableInt)(dynamic_KInt);
  dynamic_KInt (*getNonNullValueOfInt)(dynamic_kref_kotlin_Int);
  dynamic_kref_kotlin_Long (*createNullableLong)(dynamic_KLong);
  dynamic_KLong (*getNonNullValueOfLong)(dynamic_kref_kotlin_Long);
  dynamic_kref_kotlin_Float (*createNullableFloat)(dynamic_KFloat);
  dynamic_KFloat (*getNonNullValueOfFloat)(dynamic_kref_kotlin_Float);
  dynamic_kref_kotlin_Double (*createNullableDouble)(dynamic_KDouble);
  dynamic_KDouble (*getNonNullValueOfDouble)(dynamic_kref_kotlin_Double);
  dynamic_kref_kotlin_Char (*createNullableChar)(dynamic_KChar);
  dynamic_KChar (*getNonNullValueOfChar)(dynamic_kref_kotlin_Char);
  dynamic_kref_kotlin_Boolean (*createNullableBoolean)(dynamic_KBoolean);
  dynamic_KBoolean (*getNonNullValueOfBoolean)(dynamic_kref_kotlin_Boolean);
  dynamic_kref_kotlin_Unit (*createNullableUnit)(void);
  dynamic_kref_kotlin_UByte (*createNullableUByte)(dynamic_KUByte);
  dynamic_KUByte (*getNonNullValueOfUByte)(dynamic_kref_kotlin_UByte);
  dynamic_kref_kotlin_UShort (*createNullableUShort)(dynamic_KUShort);
  dynamic_KUShort (*getNonNullValueOfUShort)(dynamic_kref_kotlin_UShort);
  dynamic_kref_kotlin_UInt (*createNullableUInt)(dynamic_KUInt);
  dynamic_KUInt (*getNonNullValueOfUInt)(dynamic_kref_kotlin_UInt);
  dynamic_kref_kotlin_ULong (*createNullableULong)(dynamic_KULong);
  dynamic_KULong (*getNonNullValueOfULong)(dynamic_kref_kotlin_ULong);

  /* User functions. */
  struct {
    struct {
      struct {
        dynamic_KType* (*_type)(void);
        dynamic_kref_KNObject (*KNObject)();
        const char* (*bar)(dynamic_kref_KNObject thiz);
        void (*foo)(dynamic_kref_KNObject thiz, const char* s);
      } KNObject;
      dynamic_KInt (*add)(dynamic_KInt a, dynamic_KInt b);
      dynamic_KInt (*get5)();
      dynamic_KInt (*inc)(dynamic_KInt a);
    } root;
  } kotlin;
} dynamic_ExportedSymbols;
extern dynamic_ExportedSymbols* dynamic_symbols(void);
#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif  /* KONAN_DYNAMIC_H */
