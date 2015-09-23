#ifndef BUFRADIXSORT_PP_PRIMREC_H
#define BUFRADIXSORT_PP_PRIMREC_H

#define EMPTY

#define PRIMREC(          n, f, g, x) PRIMREC_INDIRECT1 EMPTY (n, f, g, x)
#define PRIMREC_INDIRECT1(n, f, g, x) PRIMREC_INDIRECT2 EMPTY (n, f, g, x)
#define PRIMREC_INDIRECT2(n, f, g, x) PRIMREC_##n(f, g, x)
#define PRIMREC_256(f, g, x) g EMPTY (255, x, PRIMREC_255(f, g, x))
#define PRIMREC_255(f, g, x) g EMPTY (254, x, PRIMREC_254(f, g, x))
#define PRIMREC_254(f, g, x) g EMPTY (253, x, PRIMREC_253(f, g, x))
#define PRIMREC_253(f, g, x) g EMPTY (252, x, PRIMREC_252(f, g, x))
#define PRIMREC_252(f, g, x) g EMPTY (251, x, PRIMREC_251(f, g, x))
#define PRIMREC_251(f, g, x) g EMPTY (250, x, PRIMREC_250(f, g, x))
#define PRIMREC_250(f, g, x) g EMPTY (249, x, PRIMREC_249(f, g, x))
#define PRIMREC_249(f, g, x) g EMPTY (248, x, PRIMREC_248(f, g, x))
#define PRIMREC_248(f, g, x) g EMPTY (247, x, PRIMREC_247(f, g, x))
#define PRIMREC_247(f, g, x) g EMPTY (246, x, PRIMREC_246(f, g, x))
#define PRIMREC_246(f, g, x) g EMPTY (245, x, PRIMREC_245(f, g, x))
#define PRIMREC_245(f, g, x) g EMPTY (244, x, PRIMREC_244(f, g, x))
#define PRIMREC_244(f, g, x) g EMPTY (243, x, PRIMREC_243(f, g, x))
#define PRIMREC_243(f, g, x) g EMPTY (242, x, PRIMREC_242(f, g, x))
#define PRIMREC_242(f, g, x) g EMPTY (241, x, PRIMREC_241(f, g, x))
#define PRIMREC_241(f, g, x) g EMPTY (240, x, PRIMREC_240(f, g, x))
#define PRIMREC_240(f, g, x) g EMPTY (239, x, PRIMREC_239(f, g, x))
#define PRIMREC_239(f, g, x) g EMPTY (238, x, PRIMREC_238(f, g, x))
#define PRIMREC_238(f, g, x) g EMPTY (237, x, PRIMREC_237(f, g, x))
#define PRIMREC_237(f, g, x) g EMPTY (236, x, PRIMREC_236(f, g, x))
#define PRIMREC_236(f, g, x) g EMPTY (235, x, PRIMREC_235(f, g, x))
#define PRIMREC_235(f, g, x) g EMPTY (234, x, PRIMREC_234(f, g, x))
#define PRIMREC_234(f, g, x) g EMPTY (233, x, PRIMREC_233(f, g, x))
#define PRIMREC_233(f, g, x) g EMPTY (232, x, PRIMREC_232(f, g, x))
#define PRIMREC_232(f, g, x) g EMPTY (231, x, PRIMREC_231(f, g, x))
#define PRIMREC_231(f, g, x) g EMPTY (230, x, PRIMREC_230(f, g, x))
#define PRIMREC_230(f, g, x) g EMPTY (229, x, PRIMREC_229(f, g, x))
#define PRIMREC_229(f, g, x) g EMPTY (228, x, PRIMREC_228(f, g, x))
#define PRIMREC_228(f, g, x) g EMPTY (227, x, PRIMREC_227(f, g, x))
#define PRIMREC_227(f, g, x) g EMPTY (226, x, PRIMREC_226(f, g, x))
#define PRIMREC_226(f, g, x) g EMPTY (225, x, PRIMREC_225(f, g, x))
#define PRIMREC_225(f, g, x) g EMPTY (224, x, PRIMREC_224(f, g, x))
#define PRIMREC_224(f, g, x) g EMPTY (223, x, PRIMREC_223(f, g, x))
#define PRIMREC_223(f, g, x) g EMPTY (222, x, PRIMREC_222(f, g, x))
#define PRIMREC_222(f, g, x) g EMPTY (221, x, PRIMREC_221(f, g, x))
#define PRIMREC_221(f, g, x) g EMPTY (220, x, PRIMREC_220(f, g, x))
#define PRIMREC_220(f, g, x) g EMPTY (219, x, PRIMREC_219(f, g, x))
#define PRIMREC_219(f, g, x) g EMPTY (218, x, PRIMREC_218(f, g, x))
#define PRIMREC_218(f, g, x) g EMPTY (217, x, PRIMREC_217(f, g, x))
#define PRIMREC_217(f, g, x) g EMPTY (216, x, PRIMREC_216(f, g, x))
#define PRIMREC_216(f, g, x) g EMPTY (215, x, PRIMREC_215(f, g, x))
#define PRIMREC_215(f, g, x) g EMPTY (214, x, PRIMREC_214(f, g, x))
#define PRIMREC_214(f, g, x) g EMPTY (213, x, PRIMREC_213(f, g, x))
#define PRIMREC_213(f, g, x) g EMPTY (212, x, PRIMREC_212(f, g, x))
#define PRIMREC_212(f, g, x) g EMPTY (211, x, PRIMREC_211(f, g, x))
#define PRIMREC_211(f, g, x) g EMPTY (210, x, PRIMREC_210(f, g, x))
#define PRIMREC_210(f, g, x) g EMPTY (209, x, PRIMREC_209(f, g, x))
#define PRIMREC_209(f, g, x) g EMPTY (208, x, PRIMREC_208(f, g, x))
#define PRIMREC_208(f, g, x) g EMPTY (207, x, PRIMREC_207(f, g, x))
#define PRIMREC_207(f, g, x) g EMPTY (206, x, PRIMREC_206(f, g, x))
#define PRIMREC_206(f, g, x) g EMPTY (205, x, PRIMREC_205(f, g, x))
#define PRIMREC_205(f, g, x) g EMPTY (204, x, PRIMREC_204(f, g, x))
#define PRIMREC_204(f, g, x) g EMPTY (203, x, PRIMREC_203(f, g, x))
#define PRIMREC_203(f, g, x) g EMPTY (202, x, PRIMREC_202(f, g, x))
#define PRIMREC_202(f, g, x) g EMPTY (201, x, PRIMREC_201(f, g, x))
#define PRIMREC_201(f, g, x) g EMPTY (200, x, PRIMREC_200(f, g, x))
#define PRIMREC_200(f, g, x) g EMPTY (199, x, PRIMREC_199(f, g, x))
#define PRIMREC_199(f, g, x) g EMPTY (198, x, PRIMREC_198(f, g, x))
#define PRIMREC_198(f, g, x) g EMPTY (197, x, PRIMREC_197(f, g, x))
#define PRIMREC_197(f, g, x) g EMPTY (196, x, PRIMREC_196(f, g, x))
#define PRIMREC_196(f, g, x) g EMPTY (195, x, PRIMREC_195(f, g, x))
#define PRIMREC_195(f, g, x) g EMPTY (194, x, PRIMREC_194(f, g, x))
#define PRIMREC_194(f, g, x) g EMPTY (193, x, PRIMREC_193(f, g, x))
#define PRIMREC_193(f, g, x) g EMPTY (192, x, PRIMREC_192(f, g, x))
#define PRIMREC_192(f, g, x) g EMPTY (191, x, PRIMREC_191(f, g, x))
#define PRIMREC_191(f, g, x) g EMPTY (190, x, PRIMREC_190(f, g, x))
#define PRIMREC_190(f, g, x) g EMPTY (189, x, PRIMREC_189(f, g, x))
#define PRIMREC_189(f, g, x) g EMPTY (188, x, PRIMREC_188(f, g, x))
#define PRIMREC_188(f, g, x) g EMPTY (187, x, PRIMREC_187(f, g, x))
#define PRIMREC_187(f, g, x) g EMPTY (186, x, PRIMREC_186(f, g, x))
#define PRIMREC_186(f, g, x) g EMPTY (185, x, PRIMREC_185(f, g, x))
#define PRIMREC_185(f, g, x) g EMPTY (184, x, PRIMREC_184(f, g, x))
#define PRIMREC_184(f, g, x) g EMPTY (183, x, PRIMREC_183(f, g, x))
#define PRIMREC_183(f, g, x) g EMPTY (182, x, PRIMREC_182(f, g, x))
#define PRIMREC_182(f, g, x) g EMPTY (181, x, PRIMREC_181(f, g, x))
#define PRIMREC_181(f, g, x) g EMPTY (180, x, PRIMREC_180(f, g, x))
#define PRIMREC_180(f, g, x) g EMPTY (179, x, PRIMREC_179(f, g, x))
#define PRIMREC_179(f, g, x) g EMPTY (178, x, PRIMREC_178(f, g, x))
#define PRIMREC_178(f, g, x) g EMPTY (177, x, PRIMREC_177(f, g, x))
#define PRIMREC_177(f, g, x) g EMPTY (176, x, PRIMREC_176(f, g, x))
#define PRIMREC_176(f, g, x) g EMPTY (175, x, PRIMREC_175(f, g, x))
#define PRIMREC_175(f, g, x) g EMPTY (174, x, PRIMREC_174(f, g, x))
#define PRIMREC_174(f, g, x) g EMPTY (173, x, PRIMREC_173(f, g, x))
#define PRIMREC_173(f, g, x) g EMPTY (172, x, PRIMREC_172(f, g, x))
#define PRIMREC_172(f, g, x) g EMPTY (171, x, PRIMREC_171(f, g, x))
#define PRIMREC_171(f, g, x) g EMPTY (170, x, PRIMREC_170(f, g, x))
#define PRIMREC_170(f, g, x) g EMPTY (169, x, PRIMREC_169(f, g, x))
#define PRIMREC_169(f, g, x) g EMPTY (168, x, PRIMREC_168(f, g, x))
#define PRIMREC_168(f, g, x) g EMPTY (167, x, PRIMREC_167(f, g, x))
#define PRIMREC_167(f, g, x) g EMPTY (166, x, PRIMREC_166(f, g, x))
#define PRIMREC_166(f, g, x) g EMPTY (165, x, PRIMREC_165(f, g, x))
#define PRIMREC_165(f, g, x) g EMPTY (164, x, PRIMREC_164(f, g, x))
#define PRIMREC_164(f, g, x) g EMPTY (163, x, PRIMREC_163(f, g, x))
#define PRIMREC_163(f, g, x) g EMPTY (162, x, PRIMREC_162(f, g, x))
#define PRIMREC_162(f, g, x) g EMPTY (161, x, PRIMREC_161(f, g, x))
#define PRIMREC_161(f, g, x) g EMPTY (160, x, PRIMREC_160(f, g, x))
#define PRIMREC_160(f, g, x) g EMPTY (159, x, PRIMREC_159(f, g, x))
#define PRIMREC_159(f, g, x) g EMPTY (158, x, PRIMREC_158(f, g, x))
#define PRIMREC_158(f, g, x) g EMPTY (157, x, PRIMREC_157(f, g, x))
#define PRIMREC_157(f, g, x) g EMPTY (156, x, PRIMREC_156(f, g, x))
#define PRIMREC_156(f, g, x) g EMPTY (155, x, PRIMREC_155(f, g, x))
#define PRIMREC_155(f, g, x) g EMPTY (154, x, PRIMREC_154(f, g, x))
#define PRIMREC_154(f, g, x) g EMPTY (153, x, PRIMREC_153(f, g, x))
#define PRIMREC_153(f, g, x) g EMPTY (152, x, PRIMREC_152(f, g, x))
#define PRIMREC_152(f, g, x) g EMPTY (151, x, PRIMREC_151(f, g, x))
#define PRIMREC_151(f, g, x) g EMPTY (150, x, PRIMREC_150(f, g, x))
#define PRIMREC_150(f, g, x) g EMPTY (149, x, PRIMREC_149(f, g, x))
#define PRIMREC_149(f, g, x) g EMPTY (148, x, PRIMREC_148(f, g, x))
#define PRIMREC_148(f, g, x) g EMPTY (147, x, PRIMREC_147(f, g, x))
#define PRIMREC_147(f, g, x) g EMPTY (146, x, PRIMREC_146(f, g, x))
#define PRIMREC_146(f, g, x) g EMPTY (145, x, PRIMREC_145(f, g, x))
#define PRIMREC_145(f, g, x) g EMPTY (144, x, PRIMREC_144(f, g, x))
#define PRIMREC_144(f, g, x) g EMPTY (143, x, PRIMREC_143(f, g, x))
#define PRIMREC_143(f, g, x) g EMPTY (142, x, PRIMREC_142(f, g, x))
#define PRIMREC_142(f, g, x) g EMPTY (141, x, PRIMREC_141(f, g, x))
#define PRIMREC_141(f, g, x) g EMPTY (140, x, PRIMREC_140(f, g, x))
#define PRIMREC_140(f, g, x) g EMPTY (139, x, PRIMREC_139(f, g, x))
#define PRIMREC_139(f, g, x) g EMPTY (138, x, PRIMREC_138(f, g, x))
#define PRIMREC_138(f, g, x) g EMPTY (137, x, PRIMREC_137(f, g, x))
#define PRIMREC_137(f, g, x) g EMPTY (136, x, PRIMREC_136(f, g, x))
#define PRIMREC_136(f, g, x) g EMPTY (135, x, PRIMREC_135(f, g, x))
#define PRIMREC_135(f, g, x) g EMPTY (134, x, PRIMREC_134(f, g, x))
#define PRIMREC_134(f, g, x) g EMPTY (133, x, PRIMREC_133(f, g, x))
#define PRIMREC_133(f, g, x) g EMPTY (132, x, PRIMREC_132(f, g, x))
#define PRIMREC_132(f, g, x) g EMPTY (131, x, PRIMREC_131(f, g, x))
#define PRIMREC_131(f, g, x) g EMPTY (130, x, PRIMREC_130(f, g, x))
#define PRIMREC_130(f, g, x) g EMPTY (129, x, PRIMREC_129(f, g, x))
#define PRIMREC_129(f, g, x) g EMPTY (128, x, PRIMREC_128(f, g, x))
#define PRIMREC_128(f, g, x) g EMPTY (127, x, PRIMREC_127(f, g, x))
#define PRIMREC_127(f, g, x) g EMPTY (126, x, PRIMREC_126(f, g, x))
#define PRIMREC_126(f, g, x) g EMPTY (125, x, PRIMREC_125(f, g, x))
#define PRIMREC_125(f, g, x) g EMPTY (124, x, PRIMREC_124(f, g, x))
#define PRIMREC_124(f, g, x) g EMPTY (123, x, PRIMREC_123(f, g, x))
#define PRIMREC_123(f, g, x) g EMPTY (122, x, PRIMREC_122(f, g, x))
#define PRIMREC_122(f, g, x) g EMPTY (121, x, PRIMREC_121(f, g, x))
#define PRIMREC_121(f, g, x) g EMPTY (120, x, PRIMREC_120(f, g, x))
#define PRIMREC_120(f, g, x) g EMPTY (119, x, PRIMREC_119(f, g, x))
#define PRIMREC_119(f, g, x) g EMPTY (118, x, PRIMREC_118(f, g, x))
#define PRIMREC_118(f, g, x) g EMPTY (117, x, PRIMREC_117(f, g, x))
#define PRIMREC_117(f, g, x) g EMPTY (116, x, PRIMREC_116(f, g, x))
#define PRIMREC_116(f, g, x) g EMPTY (115, x, PRIMREC_115(f, g, x))
#define PRIMREC_115(f, g, x) g EMPTY (114, x, PRIMREC_114(f, g, x))
#define PRIMREC_114(f, g, x) g EMPTY (113, x, PRIMREC_113(f, g, x))
#define PRIMREC_113(f, g, x) g EMPTY (112, x, PRIMREC_112(f, g, x))
#define PRIMREC_112(f, g, x) g EMPTY (111, x, PRIMREC_111(f, g, x))
#define PRIMREC_111(f, g, x) g EMPTY (110, x, PRIMREC_110(f, g, x))
#define PRIMREC_110(f, g, x) g EMPTY (109, x, PRIMREC_109(f, g, x))
#define PRIMREC_109(f, g, x) g EMPTY (108, x, PRIMREC_108(f, g, x))
#define PRIMREC_108(f, g, x) g EMPTY (107, x, PRIMREC_107(f, g, x))
#define PRIMREC_107(f, g, x) g EMPTY (106, x, PRIMREC_106(f, g, x))
#define PRIMREC_106(f, g, x) g EMPTY (105, x, PRIMREC_105(f, g, x))
#define PRIMREC_105(f, g, x) g EMPTY (104, x, PRIMREC_104(f, g, x))
#define PRIMREC_104(f, g, x) g EMPTY (103, x, PRIMREC_103(f, g, x))
#define PRIMREC_103(f, g, x) g EMPTY (102, x, PRIMREC_102(f, g, x))
#define PRIMREC_102(f, g, x) g EMPTY (101, x, PRIMREC_101(f, g, x))
#define PRIMREC_101(f, g, x) g EMPTY (100, x, PRIMREC_100(f, g, x))
#define PRIMREC_100(f, g, x) g EMPTY ( 99, x, PRIMREC_99( f, g, x))
#define PRIMREC_99( f, g, x) g EMPTY ( 98, x, PRIMREC_98( f, g, x))
#define PRIMREC_98( f, g, x) g EMPTY ( 97, x, PRIMREC_97( f, g, x))
#define PRIMREC_97( f, g, x) g EMPTY ( 96, x, PRIMREC_96( f, g, x))
#define PRIMREC_96( f, g, x) g EMPTY ( 95, x, PRIMREC_95( f, g, x))
#define PRIMREC_95( f, g, x) g EMPTY ( 94, x, PRIMREC_94( f, g, x))
#define PRIMREC_94( f, g, x) g EMPTY ( 93, x, PRIMREC_93( f, g, x))
#define PRIMREC_93( f, g, x) g EMPTY ( 92, x, PRIMREC_92( f, g, x))
#define PRIMREC_92( f, g, x) g EMPTY ( 91, x, PRIMREC_91( f, g, x))
#define PRIMREC_91( f, g, x) g EMPTY ( 90, x, PRIMREC_90( f, g, x))
#define PRIMREC_90( f, g, x) g EMPTY ( 89, x, PRIMREC_89( f, g, x))
#define PRIMREC_89( f, g, x) g EMPTY ( 88, x, PRIMREC_88( f, g, x))
#define PRIMREC_88( f, g, x) g EMPTY ( 87, x, PRIMREC_87( f, g, x))
#define PRIMREC_87( f, g, x) g EMPTY ( 86, x, PRIMREC_86( f, g, x))
#define PRIMREC_86( f, g, x) g EMPTY ( 85, x, PRIMREC_85( f, g, x))
#define PRIMREC_85( f, g, x) g EMPTY ( 84, x, PRIMREC_84( f, g, x))
#define PRIMREC_84( f, g, x) g EMPTY ( 83, x, PRIMREC_83( f, g, x))
#define PRIMREC_83( f, g, x) g EMPTY ( 82, x, PRIMREC_82( f, g, x))
#define PRIMREC_82( f, g, x) g EMPTY ( 81, x, PRIMREC_81( f, g, x))
#define PRIMREC_81( f, g, x) g EMPTY ( 80, x, PRIMREC_80( f, g, x))
#define PRIMREC_80( f, g, x) g EMPTY ( 79, x, PRIMREC_79( f, g, x))
#define PRIMREC_79( f, g, x) g EMPTY ( 78, x, PRIMREC_78( f, g, x))
#define PRIMREC_78( f, g, x) g EMPTY ( 77, x, PRIMREC_77( f, g, x))
#define PRIMREC_77( f, g, x) g EMPTY ( 76, x, PRIMREC_76( f, g, x))
#define PRIMREC_76( f, g, x) g EMPTY ( 75, x, PRIMREC_75( f, g, x))
#define PRIMREC_75( f, g, x) g EMPTY ( 74, x, PRIMREC_74( f, g, x))
#define PRIMREC_74( f, g, x) g EMPTY ( 73, x, PRIMREC_73( f, g, x))
#define PRIMREC_73( f, g, x) g EMPTY ( 72, x, PRIMREC_72( f, g, x))
#define PRIMREC_72( f, g, x) g EMPTY ( 71, x, PRIMREC_71( f, g, x))
#define PRIMREC_71( f, g, x) g EMPTY ( 70, x, PRIMREC_70( f, g, x))
#define PRIMREC_70( f, g, x) g EMPTY ( 69, x, PRIMREC_69( f, g, x))
#define PRIMREC_69( f, g, x) g EMPTY ( 68, x, PRIMREC_68( f, g, x))
#define PRIMREC_68( f, g, x) g EMPTY ( 67, x, PRIMREC_67( f, g, x))
#define PRIMREC_67( f, g, x) g EMPTY ( 66, x, PRIMREC_66( f, g, x))
#define PRIMREC_66( f, g, x) g EMPTY ( 65, x, PRIMREC_65( f, g, x))
#define PRIMREC_65( f, g, x) g EMPTY ( 64, x, PRIMREC_64( f, g, x))
#define PRIMREC_64( f, g, x) g EMPTY ( 63, x, PRIMREC_63( f, g, x))
#define PRIMREC_63( f, g, x) g EMPTY ( 62, x, PRIMREC_62( f, g, x))
#define PRIMREC_62( f, g, x) g EMPTY ( 61, x, PRIMREC_61( f, g, x))
#define PRIMREC_61( f, g, x) g EMPTY ( 60, x, PRIMREC_60( f, g, x))
#define PRIMREC_60( f, g, x) g EMPTY ( 59, x, PRIMREC_59( f, g, x))
#define PRIMREC_59( f, g, x) g EMPTY ( 58, x, PRIMREC_58( f, g, x))
#define PRIMREC_58( f, g, x) g EMPTY ( 57, x, PRIMREC_57( f, g, x))
#define PRIMREC_57( f, g, x) g EMPTY ( 56, x, PRIMREC_56( f, g, x))
#define PRIMREC_56( f, g, x) g EMPTY ( 55, x, PRIMREC_55( f, g, x))
#define PRIMREC_55( f, g, x) g EMPTY ( 54, x, PRIMREC_54( f, g, x))
#define PRIMREC_54( f, g, x) g EMPTY ( 53, x, PRIMREC_53( f, g, x))
#define PRIMREC_53( f, g, x) g EMPTY ( 52, x, PRIMREC_52( f, g, x))
#define PRIMREC_52( f, g, x) g EMPTY ( 51, x, PRIMREC_51( f, g, x))
#define PRIMREC_51( f, g, x) g EMPTY ( 50, x, PRIMREC_50( f, g, x))
#define PRIMREC_50( f, g, x) g EMPTY ( 49, x, PRIMREC_49( f, g, x))
#define PRIMREC_49( f, g, x) g EMPTY ( 48, x, PRIMREC_48( f, g, x))
#define PRIMREC_48( f, g, x) g EMPTY ( 47, x, PRIMREC_47( f, g, x))
#define PRIMREC_47( f, g, x) g EMPTY ( 46, x, PRIMREC_46( f, g, x))
#define PRIMREC_46( f, g, x) g EMPTY ( 45, x, PRIMREC_45( f, g, x))
#define PRIMREC_45( f, g, x) g EMPTY ( 44, x, PRIMREC_44( f, g, x))
#define PRIMREC_44( f, g, x) g EMPTY ( 43, x, PRIMREC_43( f, g, x))
#define PRIMREC_43( f, g, x) g EMPTY ( 42, x, PRIMREC_42( f, g, x))
#define PRIMREC_42( f, g, x) g EMPTY ( 41, x, PRIMREC_41( f, g, x))
#define PRIMREC_41( f, g, x) g EMPTY ( 40, x, PRIMREC_40( f, g, x))
#define PRIMREC_40( f, g, x) g EMPTY ( 39, x, PRIMREC_39( f, g, x))
#define PRIMREC_39( f, g, x) g EMPTY ( 38, x, PRIMREC_38( f, g, x))
#define PRIMREC_38( f, g, x) g EMPTY ( 37, x, PRIMREC_37( f, g, x))
#define PRIMREC_37( f, g, x) g EMPTY ( 36, x, PRIMREC_36( f, g, x))
#define PRIMREC_36( f, g, x) g EMPTY ( 35, x, PRIMREC_35( f, g, x))
#define PRIMREC_35( f, g, x) g EMPTY ( 34, x, PRIMREC_34( f, g, x))
#define PRIMREC_34( f, g, x) g EMPTY ( 33, x, PRIMREC_33( f, g, x))
#define PRIMREC_33( f, g, x) g EMPTY ( 32, x, PRIMREC_32( f, g, x))
#define PRIMREC_32( f, g, x) g EMPTY ( 31, x, PRIMREC_31( f, g, x))
#define PRIMREC_31( f, g, x) g EMPTY ( 30, x, PRIMREC_30( f, g, x))
#define PRIMREC_30( f, g, x) g EMPTY ( 29, x, PRIMREC_29( f, g, x))
#define PRIMREC_29( f, g, x) g EMPTY ( 28, x, PRIMREC_28( f, g, x))
#define PRIMREC_28( f, g, x) g EMPTY ( 27, x, PRIMREC_27( f, g, x))
#define PRIMREC_27( f, g, x) g EMPTY ( 26, x, PRIMREC_26( f, g, x))
#define PRIMREC_26( f, g, x) g EMPTY ( 25, x, PRIMREC_25( f, g, x))
#define PRIMREC_25( f, g, x) g EMPTY ( 24, x, PRIMREC_24( f, g, x))
#define PRIMREC_24( f, g, x) g EMPTY ( 23, x, PRIMREC_23( f, g, x))
#define PRIMREC_23( f, g, x) g EMPTY ( 22, x, PRIMREC_22( f, g, x))
#define PRIMREC_22( f, g, x) g EMPTY ( 21, x, PRIMREC_21( f, g, x))
#define PRIMREC_21( f, g, x) g EMPTY ( 20, x, PRIMREC_20( f, g, x))
#define PRIMREC_20( f, g, x) g EMPTY ( 19, x, PRIMREC_19( f, g, x))
#define PRIMREC_19( f, g, x) g EMPTY ( 18, x, PRIMREC_18( f, g, x))
#define PRIMREC_18( f, g, x) g EMPTY ( 17, x, PRIMREC_17( f, g, x))
#define PRIMREC_17( f, g, x) g EMPTY ( 16, x, PRIMREC_16( f, g, x))
#define PRIMREC_16( f, g, x) g EMPTY ( 15, x, PRIMREC_15( f, g, x))
#define PRIMREC_15( f, g, x) g EMPTY ( 14, x, PRIMREC_14( f, g, x))
#define PRIMREC_14( f, g, x) g EMPTY ( 13, x, PRIMREC_13( f, g, x))
#define PRIMREC_13( f, g, x) g EMPTY ( 12, x, PRIMREC_12( f, g, x))
#define PRIMREC_12( f, g, x) g EMPTY ( 11, x, PRIMREC_11( f, g, x))
#define PRIMREC_11( f, g, x) g EMPTY ( 10, x, PRIMREC_10( f, g, x))
#define PRIMREC_10( f, g, x) g EMPTY (  9, x, PRIMREC_9(  f, g, x))
#define PRIMREC_9(  f, g, x) g EMPTY (  8, x, PRIMREC_8(  f, g, x))
#define PRIMREC_8(  f, g, x) g EMPTY (  7, x, PRIMREC_7(  f, g, x))
#define PRIMREC_7(  f, g, x) g EMPTY (  6, x, PRIMREC_6(  f, g, x))
#define PRIMREC_6(  f, g, x) g EMPTY (  5, x, PRIMREC_5(  f, g, x))
#define PRIMREC_5(  f, g, x) g EMPTY (  4, x, PRIMREC_4(  f, g, x))
#define PRIMREC_4(  f, g, x) g EMPTY (  3, x, PRIMREC_3(  f, g, x))
#define PRIMREC_3(  f, g, x) g EMPTY (  2, x, PRIMREC_2(  f, g, x))
#define PRIMREC_2(  f, g, x) g EMPTY (  1, x, PRIMREC_1(  f, g, x))
#define PRIMREC_1(  f, g, x) g EMPTY (  0, x, PRIMREC_0(  f, g, x))
#define PRIMREC_0(  f, g, x) f EMPTY (x)

#define SUCC(n) SUCC_HELPER(n)
#define SUCC_HELPER(n) SUCC_##n
#define SUCC_255 256
#define SUCC_254 255
#define SUCC_253 254
#define SUCC_252 253
#define SUCC_251 252
#define SUCC_250 251
#define SUCC_249 250
#define SUCC_248 249
#define SUCC_247 248
#define SUCC_246 247
#define SUCC_245 246
#define SUCC_244 245
#define SUCC_243 244
#define SUCC_242 243
#define SUCC_241 242
#define SUCC_240 241
#define SUCC_239 240
#define SUCC_238 239
#define SUCC_237 238
#define SUCC_236 237
#define SUCC_235 236
#define SUCC_234 235
#define SUCC_233 234
#define SUCC_232 233
#define SUCC_231 232
#define SUCC_230 231
#define SUCC_229 230
#define SUCC_228 229
#define SUCC_227 228
#define SUCC_226 227
#define SUCC_225 226
#define SUCC_224 225
#define SUCC_223 224
#define SUCC_222 223
#define SUCC_221 222
#define SUCC_220 221
#define SUCC_219 220
#define SUCC_218 219
#define SUCC_217 218
#define SUCC_216 217
#define SUCC_215 216
#define SUCC_214 215
#define SUCC_213 214
#define SUCC_212 213
#define SUCC_211 212
#define SUCC_210 211
#define SUCC_209 210
#define SUCC_208 209
#define SUCC_207 208
#define SUCC_206 207
#define SUCC_205 206
#define SUCC_204 205
#define SUCC_203 204
#define SUCC_202 203
#define SUCC_201 202
#define SUCC_200 201
#define SUCC_199 200
#define SUCC_198 199
#define SUCC_197 198
#define SUCC_196 197
#define SUCC_195 196
#define SUCC_194 195
#define SUCC_193 194
#define SUCC_192 193
#define SUCC_191 192
#define SUCC_190 191
#define SUCC_189 190
#define SUCC_188 189
#define SUCC_187 188
#define SUCC_186 187
#define SUCC_185 186
#define SUCC_184 185
#define SUCC_183 184
#define SUCC_182 183
#define SUCC_181 182
#define SUCC_180 181
#define SUCC_179 180
#define SUCC_178 179
#define SUCC_177 178
#define SUCC_176 177
#define SUCC_175 176
#define SUCC_174 175
#define SUCC_173 174
#define SUCC_172 173
#define SUCC_171 172
#define SUCC_170 171
#define SUCC_169 170
#define SUCC_168 169
#define SUCC_167 168
#define SUCC_166 167
#define SUCC_165 166
#define SUCC_164 165
#define SUCC_163 164
#define SUCC_162 163
#define SUCC_161 162
#define SUCC_160 161
#define SUCC_159 160
#define SUCC_158 159
#define SUCC_157 158
#define SUCC_156 157
#define SUCC_155 156
#define SUCC_154 155
#define SUCC_153 154
#define SUCC_152 153
#define SUCC_151 152
#define SUCC_150 151
#define SUCC_149 150
#define SUCC_148 149
#define SUCC_147 148
#define SUCC_146 147
#define SUCC_145 146
#define SUCC_144 145
#define SUCC_143 144
#define SUCC_142 143
#define SUCC_141 142
#define SUCC_140 141
#define SUCC_139 140
#define SUCC_138 139
#define SUCC_137 138
#define SUCC_136 137
#define SUCC_135 136
#define SUCC_134 135
#define SUCC_133 134
#define SUCC_132 133
#define SUCC_131 132
#define SUCC_130 131
#define SUCC_129 130
#define SUCC_128 129
#define SUCC_127 128
#define SUCC_126 127
#define SUCC_125 126
#define SUCC_124 125
#define SUCC_123 124
#define SUCC_122 123
#define SUCC_121 122
#define SUCC_120 121
#define SUCC_119 120
#define SUCC_118 119
#define SUCC_117 118
#define SUCC_116 117
#define SUCC_115 116
#define SUCC_114 115
#define SUCC_113 114
#define SUCC_112 113
#define SUCC_111 112
#define SUCC_110 111
#define SUCC_109 110
#define SUCC_108 109
#define SUCC_107 108
#define SUCC_106 107
#define SUCC_105 106
#define SUCC_104 105
#define SUCC_103 104
#define SUCC_102 103
#define SUCC_101 102
#define SUCC_100 101
#define SUCC_99  100
#define SUCC_98  99
#define SUCC_97  98
#define SUCC_96  97
#define SUCC_95  96
#define SUCC_94  95
#define SUCC_93  94
#define SUCC_92  93
#define SUCC_91  92
#define SUCC_90  91
#define SUCC_89  90
#define SUCC_88  89
#define SUCC_87  88
#define SUCC_86  87
#define SUCC_85  86
#define SUCC_84  85
#define SUCC_83  84
#define SUCC_82  83
#define SUCC_81  82
#define SUCC_80  81
#define SUCC_79  80
#define SUCC_78  79
#define SUCC_77  78
#define SUCC_76  77
#define SUCC_75  76
#define SUCC_74  75
#define SUCC_73  74
#define SUCC_72  73
#define SUCC_71  72
#define SUCC_70  71
#define SUCC_69  70
#define SUCC_68  69
#define SUCC_67  68
#define SUCC_66  67
#define SUCC_65  66
#define SUCC_64  65
#define SUCC_63  64
#define SUCC_62  63
#define SUCC_61  62
#define SUCC_60  61
#define SUCC_59  60
#define SUCC_58  59
#define SUCC_57  58
#define SUCC_56  57
#define SUCC_55  56
#define SUCC_54  55
#define SUCC_53  54
#define SUCC_52  53
#define SUCC_51  52
#define SUCC_50  51
#define SUCC_49  50
#define SUCC_48  49
#define SUCC_47  48
#define SUCC_46  47
#define SUCC_45  46
#define SUCC_44  45
#define SUCC_43  44
#define SUCC_42  43
#define SUCC_41  42
#define SUCC_40  41
#define SUCC_39  40
#define SUCC_38  39
#define SUCC_37  38
#define SUCC_36  37
#define SUCC_35  36
#define SUCC_34  35
#define SUCC_33  34
#define SUCC_32  33
#define SUCC_31  32
#define SUCC_30  31
#define SUCC_29  30
#define SUCC_28  29
#define SUCC_27  28
#define SUCC_26  27
#define SUCC_25  26
#define SUCC_24  25
#define SUCC_23  24
#define SUCC_22  23
#define SUCC_21  22
#define SUCC_20  21
#define SUCC_19  20
#define SUCC_18  19
#define SUCC_17  18
#define SUCC_16  17
#define SUCC_15  16
#define SUCC_14  15
#define SUCC_13  14
#define SUCC_12  13
#define SUCC_11  12
#define SUCC_10  11
#define SUCC_9   10
#define SUCC_8   9
#define SUCC_7   8
#define SUCC_6   7
#define SUCC_5   6
#define SUCC_4   5
#define SUCC_3   4
#define SUCC_2   3
#define SUCC_1   2
#define SUCC_0   1

#endif /* BUFRADIXSORT_PP_PRIMREC_H */
