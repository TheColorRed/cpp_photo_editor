// Source: https://dev.to/sgf4/foreach_COMPONENT-macro-in-c-48ic
#define N_VA_ARGS_(_100, _99, _98, _97, _96, _95, _94, _93, _92, _91, _90, _89, _88, _87, _86, _85, _84, _83, _82, _81, _80, _79, _78, _77, _76, _75, _74, _73, _72, _71, _70, _69, _68, _67, _66, _65, _64, _63, _62, _61, _60, _59, _58, _57, _56, _55, _54, _53, _52, _51, _50, _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, _39, _38, _37, _36, _35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, _23, _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8, _7, _6, _5, _4, _3, _2, _1, N, ...) N
#define N_VA_ARGS(...) N_VA_ARGS_(__VA_ARGS__ __VA_OPT__(, ) 100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)

#define FOREACH_COMPONENT_0(FN, WIDGET_NAME, PREFIX, ...)
#define FOREACH_COMPONENT_1(FN, WIDGET_NAME, PREFIX, E, ...) FN(WIDGET_NAME, PREFIX, E)
#define FOREACH_COMPONENT_2(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_1(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_3(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_2(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_4(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_3(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_5(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_4(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_6(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_5(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_7(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_6(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_8(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_7(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_9(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                 \
  FOREACH_COMPONENT_8(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_10(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_9(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_11(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_10(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_12(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_11(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_13(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_12(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_14(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_13(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_15(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_14(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_16(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_15(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_17(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_16(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_18(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_17(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_19(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_18(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_20(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_19(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_21(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_20(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_22(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_21(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_23(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_22(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_24(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_23(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_25(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_24(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_26(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_25(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_27(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_26(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_28(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_27(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_29(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_28(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_30(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_29(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_31(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_30(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_32(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_31(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_33(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_32(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_34(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_33(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_35(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_34(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_36(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_35(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_37(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_36(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_38(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_37(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_39(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_38(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_40(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_39(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_41(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_40(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_42(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_41(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_43(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_42(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_44(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_43(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_45(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_44(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_46(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_45(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_47(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_46(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_48(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_47(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_49(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_48(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_50(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_49(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_51(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_50(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_52(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_51(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_53(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_52(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_54(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_53(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_55(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_54(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_56(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_55(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_57(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_56(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_58(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_57(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_59(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_58(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_60(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_59(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_61(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_60(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_62(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_61(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_63(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_62(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_64(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_63(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_65(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_64(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_66(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_65(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_67(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_66(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_68(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_67(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_69(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_68(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_70(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_69(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_71(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_70(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_72(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_71(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_73(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_72(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_74(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_73(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_75(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_74(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_76(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_75(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_77(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_76(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_78(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_77(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_79(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_78(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_80(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_79(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_81(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_80(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_82(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_81(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_83(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_82(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_84(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_83(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_85(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_84(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_86(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_85(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_87(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_86(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_88(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_87(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_89(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_88(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_90(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_89(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_91(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_90(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_92(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_91(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_93(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_92(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_94(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_93(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_95(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_94(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_96(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_95(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_97(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_96(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_98(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_97(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_99(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                  \
  FOREACH_COMPONENT_98(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_100(FN, WIDGET_NAME, PREFIX, E, ...) \
  FN(WIDGET_NAME, PREFIX, E)                                   \
  FOREACH_COMPONENT_99(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)

#define FOREACH_COMPONENT__(FN, WIDGET_NAME, PREFIX, NARGS, ...) FOREACH_COMPONENT_##NARGS(FN, WIDGET_NAME, PREFIX, __VA_ARGS__)
#define FOREACH_COMPONENT_(FN, WIDGET_NAME, PREFIX, NARGS, ...) FOREACH_COMPONENT__(FN, WIDGET_NAME, PREFIX, NARGS, __VA_ARGS__)
#define FOREACH_COMPONENT(FN, WIDGET_NAME, PREFIX, ...) FOREACH_COMPONENT_(FN, WIDGET_NAME, PREFIX, N_VA_ARGS(__VA_ARGS__), __VA_ARGS__)
