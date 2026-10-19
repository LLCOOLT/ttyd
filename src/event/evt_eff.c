#include "evt/evt_eff.h"
#include "driver/effdrv.h"
#include "eff/n64/eff_expbom_n64.h"
#include "eff/eff_n64.h"
#include "evt/evt_cmd.h"
#include <string.h>
#ifndef NONMATCHING
#include "driver/npcdrv.h"
__declspec(section ".rodata") extern const f64 double_to_int_802c47d8;
__declspec(section ".sdata2") extern const f32 float_2_8041a238;
__declspec(section ".sdata2") extern const f32 float_3_8041a23c;
__declspec(section ".sdata2") extern const f32 float_0_8041a240;
__declspec(section ".sdata2") extern const char str_8041A244[];
__declspec(section ".sdata2") extern const u32 lbl_8041A248;
__declspec(section ".sdata2") extern const u32 zero_8041a24c;
#define EXT_LIT(sym, val) (sym)

#endif

extern EffectEntry* effKemuri1N64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effKemuri2N64Entry(s32, f32, f32, f32, f32, f32);
extern EffectEntry* effKemuri3N64Entry(f32, f32, f32, f32);
extern EffectEntry* effKemuri4N64Entry(s32, f32, f32, f32, f32, f32);
extern EffectEntry* effKemuri5N64Entry(f32, f32, f32, f32);
extern EffectEntry* effKemuri6N64Entry(s32, f32, f32, f32);
extern EffectEntry* effKemuri7N64Entry(f32, f32, f32, f32, f32);
extern EffectEntry* effFlowerN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effSnowN64Entry(s32, f32, f32, f32);
extern EffectEntry* effSstarN64Entry(s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effStardustN64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effMagic1N64Entry(s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effMagic2N64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effFallLeafN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effHokoriN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effGarekiN64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effKemuri8N64Entry(s32, f32, f32, f32);
extern EffectEntry* effSmallStarN64Entry(s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effBombN64Entry(s32, f32, f32, f32);
extern EffectEntry* effWangFlushN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effMagic3N64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effKemuri9N64Entry(s32, s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effKemuri10N64Entry(s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effRappaN64Entry(s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effStardust2N64Entry(s32, s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effRippleN64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effExplosionN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effKemuri11N64Entry(s32, f32, f32, f32);
extern EffectEntry* effOnpuN64Entry(s32, f32, f32, f32);
extern EffectEntry* effKemuri12N64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effSweatN64Entry(s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effBalloonN64Entry(s32, f32, f32, f32, f32, f32);
extern EffectEntry* effCoolLeafN64Entry(s32, f32, f32, f32);
extern EffectEntry* effBushN64Entry(s32, f32, f32, f32);
extern EffectEntry* effRotHammerSuccessN64Entry(s32, s32, s32, f32, f32, f32);
extern EffectEntry* effRotHammerFailN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effGuruguruN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effIceN64Entry(s32, f32, f32, f32);
extern EffectEntry* effStampN64Entry(s32, f32, f32, f32);
extern EffectEntry* effThruHammerN64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effRadiationN64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effThunderN64Entry(s32, f32, f32, f32, f32, f32);
extern EffectEntry* effBreathFireN64Entry(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effBrokenBarrierN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effFireRingN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effFireDustN64Entry(s32, s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effFlameN64Entry(s32, f32, f32, f32, f32);
extern EffectEntry* effBlowN64Entry(s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effBomheiN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effFireFlowerN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effRecoverHeartN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effPturnN64Entry(s32, s32, f32, f32, f32);
extern EffectEntry* effHitN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effConfettiN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effSnowfallN64Entry(s32, s32);
extern EffectEntry* effWhirlwindN64Entry(s32, s32, s32, f32);
extern EffectEntry* effThunderflareN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effCoinN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effShockN64Entry(s32, f32, f32, f32, f32, f32);
extern EffectEntry* effBalloonHeihoN64Entry(s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effRubbleN64Entry(s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effMagicHoraoN64Entry(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effLensflareN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effCrystalN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effButterflyN64Entry(s32, f32, f32, f32);
extern EffectEntry* effAkariChargeN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effAkariSflushN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effOpukuWgunN64Entry(s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effOpukuWprotectN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effOpukuWcurtainN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effOpukuJetwN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effOpukuJetwrainN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effPokopiThunderN64Entry(s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effWaterDamageN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effSnowmanN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effHolographyN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effTimestampN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effPacknBfireN64Entry(s32, s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effPokopiPipoN64Entry(s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effCloudN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effDogabonAttackN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effKamekiTornadeN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effStoneSmokeN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effPokopiPchargeN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effHagetakaFlushN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effKumokumoN64Entry(s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effVaporN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effFireSparkN64Entry(s32, s32, s32, f32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effHoraoSpellN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effSnowDustN64Entry(s32, s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effAkariPoseN64Entry(s32, s32, s32, f32, f32, f32, f32);
extern EffectEntry* effKumokumoChipN64Entry(s32, f32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effFireworksN64Entry(s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effGlassN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effBoobooN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effPikkyoloN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effFreezeN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effSunlightN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effReleaseN64Entry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effPeachDustN64Entry(s32, f32, f32, f32, f32, f32);
extern EffectEntry* effStarPowerN64Entry(s32, s32, f32, f32, f32, f32);
extern f32 evtGetFloat(EventEntry* entry, s32 index);

extern EffectEntry* effKemuriEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effKemuTestEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effStarStoneEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effConfettiEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effButterflyEntry(s32, f32, f32, f32);
extern EffectEntry* effRecoveryEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effBreathFireEntry(s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effHitEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effBombEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effChargeEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effTogeFlushEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effIceEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effDamageStarEntry(s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effStarPointEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effItemGetEntry(s32, f32, f32, f32);
extern EffectEntry* effStageClearEntry(s32, f32, f32, f32);
extern EffectEntry* effLevelupEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effFallEntry(s32, s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effMahojinEntry(s32, f32, f32, f32);
extern EffectEntry* effNozleEntry(s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effPuniBalloonEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effKissEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effSplashEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effNiceEntry(s32, f32, f32, f32);
extern EffectEntry* effMistEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effMist2Entry(s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effScanningEntry(s32, f32, f32, f32);
extern EffectEntry* effParticleEntry(s32, s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effStardustEntry(s32, s32, s32, f32, f32, f32, f32, f32);
extern EffectEntry* effTreasureMapEntry(s32, f32, f32, f32);
extern EffectEntry* effSandarsEntry(s32, f32, f32, f32, f32);
extern EffectEntry* effSheepEntry(s32, f32, f32, f32);
extern EffectEntry* effRankupEntry(s32, f32, f32, f32);
extern EffectEntry* effIrekaeruEntry(s32, f32, f32, f32);
extern EffectEntry* effSmallStarEntry(s32, s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effIbukiEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effMahornEntry(s32, s32, s32, f32, f32, f32, f32);
extern EffectEntry* effToikiEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effUranokoEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effSyuryouEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effHibashiraEntry(s32, s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effFireEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effMachinegunEntry(s32, f32, f32, f32, f32, f32, f32);
extern EffectEntry* effRippleEntry(s32, f32, f32, f32);
extern EffectEntry* effLasMonEntry(s32, f32, f32, f32);
extern EffectEntry* effLaserEntry(s32, f32, f32, f32);
extern EffectEntry* effIndirectEntry(s32, s32, f32, f32, f32);
extern EffectEntry* effQueenEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effQueen2Entry(s32, f32, f32, f32);
extern EffectEntry* effGonbabaBreathEntry(s32, s32, f32, f32, f32, f32);
extern EffectEntry* effMajinaiEntry(s32, f32, f32, f32);

#ifdef NONMATCHING
USER_FUNC(evt_eff) {
	s32* args = event->args;
	s32* p;
	EffectEntry* entry;
	const char* effName;
	s32 int2, int3, int4, int5, int6, int7, int8, int9;
	const char* effSet;
	s32 int10, int11, int12, int13, int14;
	f32 float2, float3, float4, float5, float6, float7, float8,
		float9, float10, float11, float12, float13, float14;

	effName = (const char*)evtGetValue(event, args[0]);
	evtGetValue(event, args[0]);
	evtGetValue(event, args[0]);
	effSet = (const char*)evtGetValue(event, args[1]);
	evtGetValue(event, args[1]);
	evtGetValue(event, args[1]);
	int2 = evtGetValue(event, args[2]);
	int3 = evtGetValue(event, args[3]);
	int4 = evtGetValue(event, args[4]);
	int5 = evtGetValue(event, args[5]);
	int6 = evtGetValue(event, args[6]);
	int7 = evtGetValue(event, args[7]);
	int8 = evtGetValue(event, args[8]);
	int9 = evtGetValue(event, args[9]);
	int10 = evtGetValue(event, args[10]);
	int11 = evtGetValue(event, args[11]);
	int12 = evtGetValue(event, args[12]);
	int13 = evtGetValue(event, args[13]);
	int14 = evtGetValue(event, args[14]);
	float2 = evtGetFloat(event, args[2]);
	float3 = evtGetFloat(event, args[3]);
	float4 = evtGetFloat(event, args[4]);
	float5 = evtGetFloat(event, args[5]);
	float6 = evtGetFloat(event, args[6]);
	float7 = evtGetFloat(event, args[7]);
	float8 = evtGetFloat(event, args[8]);
	float9 = evtGetFloat(event, args[9]);
	float10 = evtGetFloat(event, args[10]);
	float11 = evtGetFloat(event, args[11]);
	float12 = evtGetFloat(event, args[12]);
	float13 = evtGetFloat(event, args[13]);
	float14 = evtGetFloat(event, args[14]);

	entry = NULL;
	switch (effGetSet(effSet)->id) {
		case 0:
			entry = effKemuriEntry(int2, float3, float4, float5, float6);
			break;
		case 28:
			entry = effKemuTestEntry(int2, float3, float4, float5, float6);
			break;
		case 29:
			entry = effStarStoneEntry(int2, float3, float4, float5, float6);
			break;
		case 1:
			entry = effConfettiEntry(int2, int6, float3, float4, float5);
			break;
		case 3:
			entry = effButterflyEntry(int2, float3, float4, float5);
			break;
		case 10:
			entry = effRecoveryEntry(int2, int6, float3, float4, float5);
			break;
		case 13:
			entry = effBreathFireEntry(int2, int9, int10, int11, float3, float4, float5, float6, float7, float8);
			((f32*)entry->userdata)[14] = float12;
			((f32*)entry->userdata)[12] = float12;
			((f32*)entry->userdata)[13] = float13;
			break;
		case 4:
			entry = effHitEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 22:
			entry = effBombEntry(int2, float3, float4, float5, float6);
			break;
		case 18:
			entry = effChargeEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 19:
			entry = effTogeFlushEntry(int2, int6, float3, float4, float5);
			break;
		case 20:
			entry = effIceEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 5:
			entry = effDamageStarEntry(int2, int8, float3, float4, float5, (f32)int6, (f32)int7);
			break;
		case 25:
			entry = effStarPointEntry(int2, int6, float3, float4, float5);
			break;
		case 30:
			entry = effItemGetEntry(int2, float3, float4, float5);
			break;
		case 34:
			entry = effStageClearEntry(int2, float3, float4, float5);
			break;
		case 33:
			entry = effLevelupEntry(int2, int6, float3, float4, float5);
			break;
		case 35:
			entry = effFallEntry(int2, int9, int10, float3, float4, float5, float6, float7, float8);
			break;
		case 39:
			entry = effMahojinEntry(int2, float3, float4, float5);
			break;
		case 40:
			entry = effNozleEntry(int2, int8, float3, float4, float5, float6, float7);
			break;
		case 26:
			entry = effPuniBalloonEntry(int2, float3, float4, float5, float6);
			break;
		case 45:
			entry = effKissEntry(int2, float3, float4, float5, float6);
			break;
		case 43:
			entry = effSplashEntry(int2, float3, float4, float5, float6);
			break;
		case 12:
			entry = effNiceEntry(int2, float3, float4, float5);
			break;
		case 47:
			entry = effMistEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 58:
			entry = effMist2Entry(int2, int8, float3, float4, float5, float6, float7);
			break;
		case 56:
			entry = effScanningEntry(int2, float3, float4, float5);
			break;
		case 59:
			entry = effParticleEntry(int2, int9, int10, float3, float4, float5, float6, float7, float8);
			break;
		case 9:
			effStardustEntry(int2, int8, int9, float3, float4, float5, float6, float7);
			break;
		case 44:
			entry = effTreasureMapEntry(int2, float3, float4, float5);
			break;
		case 52:
			entry = effSandarsEntry(int2, float3, float4, float5, (f32)int6);
			break;
		case 50:
			entry = effSheepEntry(int2, float3, float4, float5);
			break;
		case 55:
			entry = effRankupEntry(int2, float3, float4, float5);
			break;
		case 54:
			entry = effIrekaeruEntry(int2, float3, float4, float5);
			break;
		case 6:
			entry = effSmallStarEntry(int2, int9, float3, float4, float5, float6, float7, float8);
			break;
		case 60:
			entry = effIbukiEntry(int2, int6, float3, float4, float5);
			break;
		case 61:
			entry = effMahornEntry(int2, int7, int8, float3, float4, float5, float6);
			break;
		case 57:
			entry = effToikiEntry(int2, int6, float3, float4, float5);
			break;
		case 65:
			entry = effUranokoEntry(int2, int6, float3, float4, float5);
			break;
		case 64:
			entry = effSyuryouEntry(int2, int6, float3, float4, float5);
			break;
		case 66:
			entry = effHibashiraEntry(int2, int9, int11, float3, float4, float5, float6, float7, float8, float10);
			break;
		case 21:
			entry = effFireEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 69:
			entry = effMachinegunEntry(int2, float3, float4, float5, float6, float7, float8);
			break;
		case 23:
			entry = effRippleEntry(int2, float3, float4, float5);
			break;
		case 70:
			entry = effLasMonEntry(int2, float3, float4, float5);
			break;
		case 68:
			entry = effLaserEntry(int2, float3, float4, float5);
			break;
		case 63:
			entry = effIndirectEntry(int2, int6, float3, float4, float5);
			break;
		case 75:
			entry = effQueenEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 76:
			entry = effQueen2Entry(int2, float3, float4, float5);
			break;
		case 77:
			entry = effGonbabaBreathEntry(int2, int7, float3, float4, float5, float6);
			break;
		case 78:
			entry = effMajinaiEntry(int2, float3, float4, float5);
			break;

		default:
			break;
#endif
#ifndef NONMATCHING
s32 evt_eff(EventEntry* event, BOOL isFirstCall);
s32 evtGetValue(EventEntry* entry, s32 index);
int strcmp(const char *s1, const char *s2);
extern EffectEntry* effFukidashiEntry(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, f32 w, f32 e);
extern s32 marioGetExtraPartyId(void);
extern s32 marioGetPartyId(void);
extern void* marioGetPtr(void);
extern void* partyGetPtr(s32 id);
extern void* jumptable_8030AA2C[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_eff(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF20
		opword 0x7C0802A6
		opword 0x900100E4
		opword 0xDBE100D0
		opword 0xF3E100D8
		opword 0xDBC100C0
		opword 0xF3C100C8
		opword 0xDBA100B0
		opword 0xF3A100B8
		opword 0xDB8100A0
		opword 0xF38100A8
		opword 0xDB610090
		opword 0xF3610098
		opword 0xDB410080
		opword 0xF3410088
		opword 0xDB210070
		opword 0xF3210078
		opword 0xDB010060
		opword 0xF3010068
		opword 0xDAE10050
		opword 0xF2E10058
		opword 0xBE810020
		opword 0x7C7A1B78
		opword 0x83630018
		opword 0x809B0000
		bl evtGetValue
		opword 0x809B0000
		opword 0x7C7F1B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x809B0000
		opword 0x7F43D378
		bl evtGetValue
		opword 0x809B0004
		opword 0x7F43D378
		opword 0x3B3B0008
		bl evtGetValue
		opword 0x809B0004
		opword 0x7C771B78
		opword 0x7F43D378
		opword 0x7F38CB78
		bl evtGetValue
		opword 0x809B0004
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990000
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990004
		opword 0x7C7E1B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990008
		opword 0x7F43D378
		bl evtGetValue
		opword 0x8099000C
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990010
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990014
		opword 0x7C7D1B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990018
		opword 0x7C7C1B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x8099001C
		opword 0x7C7B1B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990020
		opword 0x7C761B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990024
		opword 0x7C751B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990028
		opword 0x7C741B78
		opword 0x7F43D378
		bl evtGetValue
		opword 0x8099002C
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80990030
		opword 0x7F43D378
		bl evtGetValue
		opword 0x80980000
		opword 0x7F43D378
		bl evtGetFloat
		opword 0x80980004
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFFA00890
		opword 0x80980008
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFF800890
		opword 0x8098000C
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFF600890
		opword 0x80980010
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFF400890
		opword 0x80980014
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFF200890
		opword 0x80980018
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFF000890
		opword 0x8098001C
		opword 0x7F43D378
		bl evtGetFloat
		opword 0x80980020
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFEE00890
		opword 0x80980024
		opword 0x7F43D378
		bl evtGetFloat
		opword 0x80980028
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x8098002C
		opword 0x7F43D378
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x80980030
		opword 0x7F43D378
		bl evtGetFloat
		opword 0x7EE3BB78
		opword 0x3AE00000
		bl effGetSet
		opword 0xA8030000
		opword 0x2800004E
		opword 0x4181073C
		lis r3, jumptable_8030AA2C@ha
		opword 0x5400103A
		addi r3, r3, jumptable_8030AA2C@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effKemuriEntry
		opword 0x7C771B78
		opword 0x48000704
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effKemuTestEntry
		opword 0x7C771B78
		opword 0x480006E4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effStarStoneEntry
		opword 0x7C771B78
		opword 0x480006C4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effConfettiEntry
		opword 0x7C771B78
		opword 0x480006A4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effButterflyEntry
		opword 0x7C771B78
		opword 0x48000688
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effRecoveryEntry
		opword 0x7C771B78
		opword 0x48000668
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7EC4B378
		opword 0xFC60D890
		opword 0x7EA5AB78
		opword 0xFC80D090
		opword 0x7E86A378
		opword 0xFCA0C890
		opword 0xFCC0C090
		bl effBreathFireEntry
		opword 0x7C771B78
		opword 0x8063000C
		opword 0xD3C30038
		opword 0x8077000C
		opword 0xD3C30030
		opword 0x8077000C
		opword 0xD3E30034
		opword 0x4800061C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effHitEntry
		opword 0x7C771B78
		opword 0x480005F8
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effBombEntry
		opword 0x7C771B78
		opword 0x480005D8
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effChargeEntry
		opword 0x7C771B78
		opword 0x480005B4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effTogeFlushEntry
		opword 0x7C771B78
		opword 0x48000594
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effIceEntry
		opword 0x7C771B78
		opword 0x48000570
		opword 0x3CA04330
		opword 0x6FA38000
		opword 0x9061000C
		opword 0x6F808000
		lis r4, double_to_int_802c47d8@ha
		opword 0xFC20E890
		opword 0x90A10008
		opword 0xFC40E090
		lfd f5, double_to_int_802c47d8@l(r4)
		opword 0xFC60D890
		opword 0xC8010008
		opword 0x90010014
		opword 0x7FC3F378
		opword 0xEC802828
		opword 0x7F64DB78
		opword 0x90A10010
		opword 0xC8010010
		opword 0xECA02828
		bl effDamageStarEntry
		opword 0x7C771B78
		opword 0x4800051C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effStarPointEntry
		opword 0x7C771B78
		opword 0x480004FC
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effItemGetEntry
		opword 0x7C771B78
		opword 0x480004E0
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effStageClearEntry
		opword 0x7C771B78
		opword 0x480004C4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effLevelupEntry
		opword 0x7C771B78
		opword 0x480004A4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7EC4B378
		opword 0xFC60D890
		opword 0x7EA5AB78
		opword 0xFC80D090
		opword 0xFCA0C890
		opword 0xFCC0C090
		bl effFallEntry
		opword 0x7C771B78
		opword 0x48000474
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effMahojinEntry
		opword 0x7C771B78
		opword 0x48000458
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F64DB78
		opword 0xFC60D890
		opword 0xFC80D090
		opword 0xFCA0C890
		bl effNozleEntry
		opword 0x7C771B78
		opword 0x48000430
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effPuniBalloonEntry
		opword 0x7C771B78
		opword 0x48000410
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effKissEntry
		opword 0x7C771B78
		opword 0x480003F0
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		bl effSplashEntry
		opword 0x7C771B78
		opword 0x480003D0
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effNiceEntry
		opword 0x7C771B78
		opword 0x480003B4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effMistEntry
		opword 0x7C771B78
		opword 0x48000390
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F64DB78
		opword 0xFC60D890
		opword 0xFC80D090
		opword 0xFCA0C890
		bl effMist2Entry
		opword 0x7C771B78
		opword 0x48000368
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effScanningEntry
		opword 0x7C771B78
		opword 0x4800034C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7EC4B378
		opword 0xFC60D890
		opword 0x7EA5AB78
		opword 0xFC80D090
		opword 0xFCA0C890
		opword 0xFCC0C090
		bl effParticleEntry
		opword 0x7C771B78
		opword 0x4800031C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F64DB78
		opword 0xFC60D890
		opword 0x7EC5B378
		opword 0xFC80D090
		opword 0xFCA0C890
		bl effStardustEntry
		opword 0x480002F4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effTreasureMapEntry
		opword 0x7C771B78
		opword 0x480002D8
		opword 0x6FA38000
		opword 0x3C004330
		opword 0x90610014
		lis r4, double_to_int_802c47d8@ha
		lfd f4, double_to_int_802c47d8@l(r4)
		opword 0xFC20E890
		opword 0x90010010
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0x7FC3F378
		opword 0xC8010010
		opword 0xEC802028
		bl effSandarsEntry
		opword 0x7C771B78
		opword 0x4800029C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effSheepEntry
		opword 0x7C771B78
		opword 0x48000280
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effRankupEntry
		opword 0x7C771B78
		opword 0x48000264
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effIrekaeruEntry
		opword 0x7C771B78
		opword 0x48000248
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7EC4B378
		opword 0xFC60D890
		opword 0xFC80D090
		opword 0xFCA0C890
		opword 0xFCC0C090
		bl effSmallStarEntry
		opword 0x7C771B78
		opword 0x4800021C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effIbukiEntry
		opword 0x7C771B78
		opword 0x480001FC
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0x7F65DB78
		opword 0xFC80D090
		bl effMahornEntry
		opword 0x7C771B78
		opword 0x480001D4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effToikiEntry
		opword 0x7C771B78
		opword 0x480001B4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effUranokoEntry
		opword 0x7C771B78
		opword 0x48000194
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effSyuryouEntry
		opword 0x7C771B78
		opword 0x48000174
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7EC4B378
		opword 0xFC60D890
		opword 0x7E85A378
		opword 0xFC80D090
		opword 0xFCA0C890
		opword 0xFCC0C090
		opword 0xFCE0B890
		bl effHibashiraEntry
		opword 0x7C771B78
		opword 0x48000140
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effFireEntry
		opword 0x7C771B78
		opword 0x4800011C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		opword 0xFC80D090
		opword 0xFCA0C890
		opword 0xFCC0C090
		bl effMachinegunEntry
		opword 0x7C771B78
		opword 0x480000F4
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effRippleEntry
		opword 0x7C771B78
		opword 0x480000D8
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effLasMonEntry
		opword 0x7C771B78
		opword 0x480000BC
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effLaserEntry
		opword 0x7C771B78
		opword 0x480000A0
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7FA4EB78
		opword 0xFC60D890
		bl effIndirectEntry
		opword 0x7C771B78
		opword 0x48000080
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effQueenEntry
		opword 0x7C771B78
		opword 0x4800005C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effQueen2Entry
		opword 0x7C771B78
		opword 0x48000040
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0x7F84E378
		opword 0xFC60D890
		opword 0xFC80D090
		bl effGonbabaBreathEntry
		opword 0x7C771B78
		opword 0x4800001C
		opword 0xFC20E890
		opword 0x7FC3F378
		opword 0xFC40E090
		opword 0xFC60D890
		bl effMajinaiEntry
		opword 0x7C771B78
		opword 0x28170000
		opword 0x4182002C
		opword 0x281F0000
		opword 0x41820024
		opword 0x7FE3FB78
		la r4, lbl_8041A248(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x7EE3BB78
		opword 0x7FE4FB78
		bl effSetName
		opword 0x38600002
		opword 0xE3E100D8
		opword 0xCBE100D0
		opword 0xE3C100C8
		opword 0xCBC100C0
		opword 0xE3A100B8
		opword 0xCBA100B0
		opword 0xE38100A8
		opword 0xCB8100A0
		opword 0xE3610098
		opword 0xCB610090
		opword 0xE3410088
		opword 0xCB410080
		opword 0xE3210078
		opword 0xCB210070
		opword 0xE3010068
		opword 0xCB010060
		opword 0xE2E10058
		opword 0xCAE10050
		opword 0xBA810020
		opword 0x800100E4
		opword 0x7C0803A6
		opword 0x382100E0
#endif
	}
#ifdef NONMATCHING

	if (entry && effName) {
		if (strcmp(effName, "")) {
			effSetName(entry, effName);
		}
	}

	return EVT_RETURN_DONE;
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif




#pragma push
#pragma optimization_level 2
#ifdef NONMATCHING
s32 evt_eff64(EventEntry *event, BOOL isFirstCall)
{
  s32 *args;
  s32 *pi;
  s32 *pf;
  s32 *pr;
  s32 new_var;
  const char *effName;
  const char *effSet;
  s32 int2;
  s32 int3;
  s32 int4;
  s32 int5;
  s32 int6;
  s32 int7;
  s32 int8;
  s32 int9;
  s32 int10;
  s32 int11;
  s32 int12;
  s32 int13;
  s32 int14;
  s32 raw3;
  f32 float2;
  f32 float3;
  f32 float4;
  f32 float5;
  f32 float6;
  f32 float7;
  f32 float8;
  f32 float9;
  f32 float10;
  f32 float11;
  f32 float12;
  f32 float13;
  f32 float14;
  EffectEntry *effect;
  s32 u0a;
  s32 u0b;
  s32 u1a;
  s32 u1b;
  args = event->args;
  effName = (const char *) evtGetValue(event, args[0]);
  evtGetValue(event, args[0]);
  evtGetValue(event, args[0]);
  pi = args + 2;
  effSet = (const char *) evtGetValue(event, args[1]);
  pr = pi;
  u1a = evtGetValue(event, args[1]);
  pf = pi;
  u1b = evtGetValue(event, args[1]);
  int2 = evtGetValue(event, *(pi++));
  int3 = evtGetValue(event, *(pi++));
  int4 = evtGetValue(event, *(pi++));
  int5 = evtGetValue(event, *(pi++));
  int6 = evtGetValue(event, *(pi++));
  int7 = evtGetValue(event, *(pi++));
  int8 = evtGetValue(event, *(pi++));
  int9 = evtGetValue(event, *(pi++));
  int10 = evtGetValue(event, *(pi++));
  int11 = evtGetValue(event, *(pi++));
  int12 = evtGetValue(event, *(pi++));
  int13 = evtGetValue(event, *(pi++));
  int14 = evtGetValue(event, *(pi++));
  float2 = evtGetFloat(event, *(pr++));
  float3 = evtGetFloat(event, *(pr++));
  float4 = evtGetFloat(event, *(pr++));
  float5 = evtGetFloat(event, *(pr++));
  float6 = evtGetFloat(event, *(pr++));
  float7 = evtGetFloat(event, *(pr++));
  float8 = evtGetFloat(event, *(pr++));
  float9 = evtGetFloat(event, *(pr++));
  float10 = evtGetFloat(event, *(pr++));
  float11 = evtGetFloat(event, *(pr++));
  float12 = evtGetFloat(event, *(pr++));
  float13 = evtGetFloat(event, *(pr++));
  float14 = evtGetFloat(event, *(pr++));
  raw3 = pf[1];
  effect = (void *) 0;
  switch (effGetSetN64(effSet)->id)
  {
    case 0:
      effect = effExpBomN64Entry(float2, float3, float4);
      break;

    case 1:
      effect = effKemuri1N64Entry(int2, float3, float4, float5, float6);
      break;

    case 2:
      effect = effKemuri2N64Entry(int2, float3, float4, float5, float6, float7);
      break;

    case 3:
      effect = effKemuri3N64Entry(float2, float3, float4, float5);
      break;

    case 4:
      effect = effKemuri4N64Entry(int2, float3, float4, float5, float6, float7);
      break;

    case 5:
      effect = effKemuri5N64Entry(float2, float3, float4, float5);
      break;

    case 6:
      effect = effKemuri6N64Entry(int2, float3, float4, float5);
      break;

    case 7:
      effect = effKemuri7N64Entry(float2, float3, float4, float5, float6);
      break;

    case 8:
      effect = effFlowerN64Entry(int2, int6, float3, float4, float5);
      break;

    case 9:
      effect = effSnowN64Entry(int5, float2, float3, float5);
      break;

    case 10:
      effect = effSstarN64Entry(int2, float3, float4, float5, float6, float7, float8, (f32) int9);
      break;

    case 11:
      effect = effStardustN64Entry(int2, float3, float4, float5, float6);
      break;

    case 12:
      effect = effMagic1N64Entry(int2, int9, float3, float4, float5, float6, float7, float8);
      break;

    case 13:
      effect = effMagic2N64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 14:
      effect = effFallLeafN64Entry(int2, int6, float3, float4, float5);
      break;

    case 15:
      effect = effHokoriN64Entry(int2, int6, float3, float4, float5);
      break;

    case 16:
      effect = effGarekiN64Entry(int2, float3, float4, float5, float6);
      break;

    case 17:
      effect = effKemuri8N64Entry(int2, float3, float4, float5);
      break;

    case 18:
      effect = effSmallStarN64Entry(int2, int9, float3, float4, float5, float6, float7, float8);
      break;

    case 19:
      effect = effBombN64Entry(int2, float3, float4, float5);
      break;

    case 20:
      effect = effWangFlushN64Entry(int2, int6, float3, float4, float5);
      break;

    case 21:
      effect = effMagic3N64Entry(int2, int6, float3, float4, float5);
      break;

    case 22:
      effect = effKemuri9N64Entry(int2, int7, int9, float3, float4, float5, float6, float8);
      break;

    case 23:
      effect = effKemuri10N64Entry(int2, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 25:
      effect = effRappaN64Entry(int2, int8, float3, float4, float5, float6, float7);
      break;

    case 26:
      effect = effStardust2N64Entry(int2, int8, int9, float3, float4, float5, float6, float7);
      break;

    case 27:
      effect = effRippleN64Entry(int2, float3, float4, float5, float6);
      break;

    case 28:
      effect = effExplosionN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 29:
      effect = effKemuri11N64Entry(int2, float3, float4, float5);
      break;

    case 30:
      effect = effOnpuN64Entry(int2, float3, float4, float5);
      break;

    case 31:
      effect = effKemuri12N64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 32:
      effect = effSweatN64Entry(int2, int8, float3, float4, float5, float6, float7);
      break;

    case 33:
      effect = effBalloonN64Entry(int2, float3, float4, float5, float6, float7);
      break;

    case 34:
      effect = effCoolLeafN64Entry(int2, float3, float4, float5);
      break;

    new_var = int2;
    case 35:
      effect = effBushN64Entry(int2, float3, float4, float5);
      break;

    case 36:
      effect = effRotHammerSuccessN64Entry(int2, int6, int7, float3, float4, float5);
      break;

    case 37:
      effect = effRotHammerFailN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 38:
      effect = effGuruguruN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 39:
      effect = effIceN64Entry(int2, float3, float4, float5);
      break;

    case 40:
      effect = effStampN64Entry(int2, float3, float4, float5);
      break;

    case 41:
      effect = effThruHammerN64Entry(int2, float3, float4, float5, float6);
      break;

    case 42:
      effect = effRadiationN64Entry(int2, float3, float4, float5, float6);
      break;

    case 43:
      effect = effThunderN64Entry(int2, float3, float4, float5, float6, float7);
      break;

    case 44:
      effect = effBreathFireN64Entry(int2, int9, int10, int11, float3, float4, float5, float6, float7, float8);
      break;

    case 45:
      effect = effBrokenBarrierN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 46:
      effect = effFireRingN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 47:
      effect = effFireDustN64Entry(int2, int8, int9, float3, float4, float5, float6, float7);
      break;

    case 48:
      effect = effFlameN64Entry(int2, float3, float4, float5, float6);
      break;

    case 49:
      effect = effBlowN64Entry(int2, int9, float3, float4, float5, float6, float7, float8);
      break;

    case 50:
      effect = effBomheiN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 51:
      effect = effFireFlowerN64Entry(int2, int6, float3, float4, float5);
      break;

    case 52:
      effect = effRecoverHeartN64Entry(int2, int6, float3, float4, float5);
      break;

    case 53:
      effect = effPturnN64Entry(int2, int6, float3, float4, float5);
      break;

    case 54:
      effect = effHitN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 55:
      effect = effConfettiN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 56:
      effect = effSnowfallN64Entry(int2, int3);
      break;

    case 57:
      effect = effWhirlwindN64Entry(int2, raw3, int5, float4);
      break;

    case 58:
      effect = effThunderflareN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 59:
      effect = effCoinN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 60:
      effect = effShockN64Entry(int2, float3, float4, float5, float6, float7);
      break;

    case 61:
      effect = effBalloonHeihoN64Entry(int2, int8, float3, float4, float5, float6, float7);
      break;

    case 62:
      effect = effRubbleN64Entry(int2, int10, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 63:
      effMagicHoraoN64Entry(int2, int7, int9, int11, float3, float4, float5, float6, float8, float10);
      break;

    case 64:
      effect = effLensflareN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 65:
      effect = effCrystalN64Entry(new_var, int7, float3, float4, float5, float6);
      break;

    case 66:
      effect = effButterflyN64Entry(int2, float3, float4, float5);
      break;

    case 67:
      effect = effAkariChargeN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 68:
      effect = effAkariSflushN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 69:
      effect = effOpukuWgunN64Entry(int2, int10, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 70:
      effect = effOpukuWprotectN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 71:
      effect = effOpukuWcurtainN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 72:
      effect = effOpukuJetwN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 73:
      effect = effOpukuJetwrainN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 74:
      effect = effPokopiThunderN64Entry(int2, int10, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 75:
      effect = effWaterDamageN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 76:
      effect = effSnowmanN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 77:
      effect = effHolographyN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 78:
      effect = effTimestampN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 79:
      effect = effPacknBfireN64Entry(int2, int10, int11, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 80:
      effect = effPokopiPipoN64Entry(int2, int10, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 81:
      effect = effCloudN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 82:
      effect = effDogabonAttackN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 83:
      effect = effKamekiTornadeN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 84:
      effect = effStoneSmokeN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 85:
      effect = effPokopiPchargeN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 86:
      effect = effHagetakaFlushN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 87:
      effect = effKumokumoN64Entry(int2, int9, float3, float4, float5, float6, float7, float8);
      break;

    case 88:
      effect = effVaporN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 89:
      effect = effFireSparkN64Entry(int2, int9, int10, float3, float4, float5, float6, float7, float8, float11, float12);
      break;

    case 90:
      effect = effHoraoSpellN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 91:
      effect = effSnowDustN64Entry(int2, int9, int10, float3, float4, float5, float6, float7, float8);
      break;

    case 92:
      effect = effAkariPoseN64Entry(int2, int7, int8, float3, float4, float5, float6);
      break;

    case 93:
      effect = effKumokumoChipN64Entry(int2, float3, float4, float5, float6, float7, float8, float9, float10);
      break;

    case 94:
      effect = effFireworksN64Entry(int2, int10, float3, float4, float5, float6, float7, float8, float9);
      break;

    case 95:
      effect = effGlassN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 96:
      effect = effBoobooN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 97:
      effect = effPikkyoloN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 98:
      effect = effFreezeN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 99:
      effect = effSunlightN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 100:
      effect = effReleaseN64Entry(int2, int7, float3, float4, float5, float6);
      break;

    case 101:
      effect = effPeachDustN64Entry(int2, float3, float4, float5, float6, (f32) int7);
      break;

    case 102:
      effect = effStarPowerN64Entry(int2, int7, float3, float4, float5, float6);
      break;

  }

  if (effect && effName)
  {
    if (strcmp(effName, "\0\0\0"))
    {
      effSetName(effect, effName);
    }
  }
  return 2;
#endif
#ifndef NONMATCHING
s32 evt_eff64(EventEntry *event, BOOL isFirstCall);
extern void* jumptable_8030A890[];
extern void* jumptable_8030AA2C[];
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_eff64(EventEntry *event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF00
		opword 0x7C0802A6
		opword 0x90010104
		opword 0xDBE100F0
		opword 0xF3E100F8
		opword 0xDBC100E0
		opword 0xF3C100E8
		opword 0xDBA100D0
		opword 0xF3A100D8
		opword 0xDB8100C0
		opword 0xF38100C8
		opword 0xDB6100B0
		opword 0xF36100B8
		opword 0xDB4100A0
		opword 0xF34100A8
		opword 0xDB210090
		opword 0xF3210098
		opword 0xDB010080
		opword 0xF3010088
		opword 0xDAE10070
		opword 0xF2E10078
		opword 0xDAC10060
		opword 0xF2C10068
		opword 0xDAA10050
		opword 0xF2A10058
		opword 0xBE210014
		opword 0x7C7E1B78
		opword 0x82230018
		opword 0x80910000
		bl evtGetValue
		opword 0x80910000
		opword 0x7C7F1B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x80910000
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x80910004
		opword 0x7FC3F378
		opword 0x3BB10008
		bl evtGetValue
		opword 0x80910004
		opword 0x7C7A1B78
		opword 0x7FC3F378
		opword 0x7FBCEB78
		bl evtGetValue
		opword 0x80910004
		opword 0x7FC3F378
		opword 0x7FBBEB78
		bl evtGetValue
		opword 0x809D0000
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0004
		opword 0x7C791B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0008
		opword 0x7C781B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D000C
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0010
		opword 0x7C771B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0014
		opword 0x7C761B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0018
		opword 0x7C751B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D001C
		opword 0x7C741B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0020
		opword 0x7C731B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0024
		opword 0x7C721B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0028
		opword 0x7C711B78
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D002C
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809D0030
		opword 0x7FC3F378
		bl evtGetValue
		opword 0x809C0000
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x809C0004
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809C0008
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFFA00890
		opword 0x809C000C
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFF800890
		opword 0x809C0010
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFF600890
		opword 0x809C0014
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFF400890
		opword 0x809C0018
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFF200890
		opword 0x809C001C
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFF000890
		opword 0x809C0020
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFEE00890
		opword 0x809C0024
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFEC00890
		opword 0x809C0028
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0xFEA00890
		opword 0x809C002C
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0x809C0030
		opword 0x7FC3F378
		bl evtGetFloat
		opword 0x837B0004
		opword 0x7F43D378
		opword 0x3B400000
		bl effGetSetN64
		opword 0xA8030000
		opword 0x28000066
		opword 0x41810EC8
		lis r3, jumptable_8030A890@ha
		opword 0x5400103A
		addi r3, r3, jumptable_8030A890@l
		opword 0x7C03002E
		opword 0x7C0903A6
		opword 0x4E800420
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0xFC60E890
		bl effExpBomN64Entry
		opword 0x7C7A1B78
		opword 0x48000E98
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effKemuri1N64Entry
		opword 0x7C7A1B78
		opword 0x48000E78
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effKemuri2N64Entry
		opword 0x7C7A1B78
		opword 0x48000E54
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0xFC60E890
		opword 0xFC80E090
		bl effKemuri3N64Entry
		opword 0x7C7A1B78
		opword 0x48000E38
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effKemuri4N64Entry
		opword 0x7C7A1B78
		opword 0x48000E14
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0xFC60E890
		opword 0xFC80E090
		bl effKemuri5N64Entry
		opword 0x7C7A1B78
		opword 0x48000DF8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effKemuri6N64Entry
		opword 0x7C7A1B78
		opword 0x48000DDC
		opword 0xFC20F890
		opword 0xFC40F090
		opword 0xFC60E890
		opword 0xFC80E090
		opword 0xFCA0D890
		bl effKemuri7N64Entry
		opword 0x7C7A1B78
		opword 0x48000DBC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effFlowerN64Entry
		opword 0x7C7A1B78
		opword 0x48000D9C
		opword 0xFC20F890
		opword 0x7EE3BB78
		opword 0xFC40F090
		opword 0xFC60E090
		bl effSnowN64Entry
		opword 0x7C7A1B78
		opword 0x48000D80
		opword 0x6E638000
		opword 0x3C004330
		opword 0x9061000C
		lis r4, double_to_int_802c47d8@ha
		lfd f7, double_to_int_802c47d8@l(r4)
		opword 0xFC20F090
		opword 0x90010008
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0x7F23CB78
		opword 0xC8010008
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xECE03828
		bl effSstarN64Entry
		opword 0x7C7A1B78
		opword 0x48000D38
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effStardustN64Entry
		opword 0x7C7A1B78
		opword 0x48000D18
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		bl effMagic1N64Entry
		opword 0x7C7A1B78
		opword 0x48000CEC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effMagic2N64Entry
		opword 0x7C7A1B78
		opword 0x48000CC8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effFallLeafN64Entry
		opword 0x7C7A1B78
		opword 0x48000CA8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effHokoriN64Entry
		opword 0x7C7A1B78
		opword 0x48000C88
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effGarekiN64Entry
		opword 0x7C7A1B78
		opword 0x48000C68
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effKemuri8N64Entry
		opword 0x7C7A1B78
		opword 0x48000C4C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		bl effSmallStarN64Entry
		opword 0x7C7A1B78
		opword 0x48000C20
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effBombN64Entry
		opword 0x7C7A1B78
		opword 0x48000C04
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effWangFlushN64Entry
		opword 0x7C7A1B78
		opword 0x48000BE4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effMagic3N64Entry
		opword 0x7C7A1B78
		opword 0x48000BC4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0x7E659B78
		opword 0xFC80D890
		opword 0xFCA0C890
		bl effKemuri9N64Entry
		opword 0x7C7A1B78
		opword 0x48000B98
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effKemuri10N64Entry
		opword 0x7C7A1B78
		opword 0x48000B6C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E84A378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effRappaN64Entry
		opword 0x7C7A1B78
		opword 0x48000B44
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E84A378
		opword 0xFC60E090
		opword 0x7E659B78
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effStardust2N64Entry
		opword 0x7C7A1B78
		opword 0x48000B18
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effRippleN64Entry
		opword 0x7C7A1B78
		opword 0x48000AF8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effExplosionN64Entry
		opword 0x7C7A1B78
		opword 0x48000AD4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effKemuri11N64Entry
		opword 0x7C7A1B78
		opword 0x48000AB8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effOnpuN64Entry
		opword 0x7C7A1B78
		opword 0x48000A9C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effKemuri12N64Entry
		opword 0x7C7A1B78
		opword 0x48000A78
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E84A378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effSweatN64Entry
		opword 0x7C7A1B78
		opword 0x48000A50
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effBalloonN64Entry
		opword 0x7C7A1B78
		opword 0x48000A2C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effCoolLeafN64Entry
		opword 0x7C7A1B78
		opword 0x48000A10
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effBushN64Entry
		opword 0x7C7A1B78
		opword 0x480009F4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		opword 0x7EA5AB78
		bl effRotHammerSuccessN64Entry
		opword 0x7C7A1B78
		opword 0x480009D0
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effRotHammerFailN64Entry
		opword 0x7C7A1B78
		opword 0x480009AC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effGuruguruN64Entry
		opword 0x7C7A1B78
		opword 0x48000988
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effIceN64Entry
		opword 0x7C7A1B78
		opword 0x4800096C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effStampN64Entry
		opword 0x7C7A1B78
		opword 0x48000950
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effThruHammerN64Entry
		opword 0x7C7A1B78
		opword 0x48000930
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effRadiationN64Entry
		opword 0x7C7A1B78
		opword 0x48000910
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effThunderN64Entry
		opword 0x7C7A1B78
		opword 0x480008EC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0x7E459378
		opword 0xFC80D890
		opword 0x7E268B78
		opword 0xFCA0D090
		opword 0xFCC0C890
		bl effBreathFireN64Entry
		opword 0x7C7A1B78
		opword 0x480008B8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effBrokenBarrierN64Entry
		opword 0x7C7A1B78
		opword 0x48000894
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effFireRingN64Entry
		opword 0x7C7A1B78
		opword 0x48000870
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E84A378
		opword 0xFC60E090
		opword 0x7E659B78
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effFireDustN64Entry
		opword 0x7C7A1B78
		opword 0x48000844
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		bl effFlameN64Entry
		opword 0x7C7A1B78
		opword 0x48000824
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		bl effBlowN64Entry
		opword 0x7C7A1B78
		opword 0x480007F8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effBomheiN64Entry
		opword 0x7C7A1B78
		opword 0x480007D4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effFireFlowerN64Entry
		opword 0x7C7A1B78
		opword 0x480007B4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effRecoverHeartN64Entry
		opword 0x7C7A1B78
		opword 0x48000794
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EC4B378
		opword 0xFC60E090
		bl effPturnN64Entry
		opword 0x7C7A1B78
		opword 0x48000774
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effHitN64Entry
		opword 0x7C7A1B78
		opword 0x48000750
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effConfettiN64Entry
		opword 0x7C7A1B78
		opword 0x4800072C
		opword 0x7F23CB78
		opword 0x7F04C378
		bl effSnowfallN64Entry
		opword 0x7C7A1B78
		opword 0x48000718
		opword 0xFC20E890
		opword 0x7F23CB78
		opword 0x7F64DB78
		opword 0x7EE5BB78
		bl effWhirlwindN64Entry
		opword 0x7C7A1B78
		opword 0x480006FC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effThunderflareN64Entry
		opword 0x7C7A1B78
		opword 0x480006D8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effCoinN64Entry
		opword 0x7C7A1B78
		opword 0x480006B4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effShockN64Entry
		opword 0x7C7A1B78
		opword 0x48000690
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E84A378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		bl effBalloonHeihoN64Entry
		opword 0x7C7A1B78
		opword 0x48000668
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E449378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effRubbleN64Entry
		opword 0x7C7A1B78
		opword 0x48000638
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0x7E659B78
		opword 0xFC80D890
		opword 0x7E268B78
		opword 0xFCA0C890
		opword 0xFCC0B890
		bl effMagicHoraoN64Entry
		opword 0x48000608
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effLensflareN64Entry
		opword 0x7C7A1B78
		opword 0x480005E4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effCrystalN64Entry
		opword 0x7C7A1B78
		opword 0x480005C0
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		bl effButterflyN64Entry
		opword 0x7C7A1B78
		opword 0x480005A4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effAkariChargeN64Entry
		opword 0x7C7A1B78
		opword 0x48000580
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effAkariSflushN64Entry
		opword 0x7C7A1B78
		opword 0x4800055C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E449378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effOpukuWgunN64Entry
		opword 0x7C7A1B78
		opword 0x4800052C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effOpukuWprotectN64Entry
		opword 0x7C7A1B78
		opword 0x48000508
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effOpukuWcurtainN64Entry
		opword 0x7C7A1B78
		opword 0x480004E4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effOpukuJetwN64Entry
		opword 0x7C7A1B78
		opword 0x480004C0
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effOpukuJetwrainN64Entry
		opword 0x7C7A1B78
		opword 0x4800049C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E449378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effPokopiThunderN64Entry
		opword 0x7C7A1B78
		opword 0x4800046C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effWaterDamageN64Entry
		opword 0x7C7A1B78
		opword 0x48000448
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effSnowmanN64Entry
		opword 0x7C7A1B78
		opword 0x48000424
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effHolographyN64Entry
		opword 0x7C7A1B78
		opword 0x48000400
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effTimestampN64Entry
		opword 0x7C7A1B78
		opword 0x480003DC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E449378
		opword 0xFC60E090
		opword 0x7E258B78
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effPacknBfireN64Entry
		opword 0x7C7A1B78
		opword 0x480003A8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E449378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effPokopiPipoN64Entry
		opword 0x7C7A1B78
		opword 0x48000378
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effCloudN64Entry
		opword 0x7C7A1B78
		opword 0x48000354
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effDogabonAttackN64Entry
		opword 0x7C7A1B78
		opword 0x48000330
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effKamekiTornadeN64Entry
		opword 0x7C7A1B78
		opword 0x4800030C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effStoneSmokeN64Entry
		opword 0x7C7A1B78
		opword 0x480002E8
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effPokopiPchargeN64Entry
		opword 0x7C7A1B78
		opword 0x480002C4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effHagetakaFlushN64Entry
		opword 0x7C7A1B78
		opword 0x480002A0
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		bl effKumokumoN64Entry
		opword 0x7C7A1B78
		opword 0x48000274
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effVaporN64Entry
		opword 0x7C7A1B78
		opword 0x48000250
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0x7E459378
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0B090
		opword 0xFD00A890
		bl effFireSparkN64Entry
		opword 0x7C7A1B78
		opword 0x48000218
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effHoraoSpellN64Entry
		opword 0x7C7A1B78
		opword 0x480001F4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E649B78
		opword 0xFC60E090
		opword 0x7E459378
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		bl effSnowDustN64Entry
		opword 0x7C7A1B78
		opword 0x480001C4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0x7E85A378
		opword 0xFC80D890
		bl effAkariPoseN64Entry
		opword 0x7C7A1B78
		opword 0x4800019C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		opword 0xFD00B890
		bl effKumokumoChipN64Entry
		opword 0x7C7A1B78
		opword 0x4800016C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7E449378
		opword 0xFC60E090
		opword 0xFC80D890
		opword 0xFCA0D090
		opword 0xFCC0C890
		opword 0xFCE0C090
		bl effFireworksN64Entry
		opword 0x7C7A1B78
		opword 0x4800013C
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effGlassN64Entry
		opword 0x7C7A1B78
		opword 0x48000118
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effBoobooN64Entry
		opword 0x7C7A1B78
		opword 0x480000F4
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effPikkyoloN64Entry
		opword 0x7C7A1B78
		opword 0x480000D0
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effFreezeN64Entry
		opword 0x7C7A1B78
		opword 0x480000AC
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effSunlightN64Entry
		opword 0x7C7A1B78
		opword 0x48000088
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effReleaseN64Entry
		opword 0x7C7A1B78
		opword 0x48000064
		opword 0x6EA38000
		opword 0x3C004330
		opword 0x9061000C
		lis r4, double_to_int_802c47d8@ha
		lfd f5, double_to_int_802c47d8@l(r4)
		opword 0xFC20F090
		opword 0x90010008
		opword 0xFC40E890
		opword 0xFC60E090
		opword 0x7F23CB78
		opword 0xC8010008
		opword 0xFC80D890
		opword 0xECA02828
		bl effPeachDustN64Entry
		opword 0x7C7A1B78
		opword 0x48000024
		opword 0xFC20F090
		opword 0x7F23CB78
		opword 0xFC40E890
		opword 0x7EA4AB78
		opword 0xFC60E090
		opword 0xFC80D890
		bl effStarPowerN64Entry
		opword 0x7C7A1B78
		opword 0x281A0000
		opword 0x4182002C
		opword 0x281F0000
		opword 0x41820024
		opword 0x7FE3FB78
		la r4, lbl_8041A248(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820010
		opword 0x7F43D378
		opword 0x7FE4FB78
		bl effSetName
		opword 0x38600002
		opword 0xE3E100F8
		opword 0xCBE100F0
		opword 0xE3C100E8
		opword 0xCBC100E0
		opword 0xE3A100D8
		opword 0xCBA100D0
		opword 0xE38100C8
		opword 0xCB8100C0
		opword 0xE36100B8
		opword 0xCB6100B0
		opword 0xE34100A8
		opword 0xCB4100A0
		opword 0xE3210098
		opword 0xCB210090
		opword 0xE3010088
		opword 0xCB010080
		opword 0xE2E10078
		opword 0xCAE10070
		opword 0xE2C10068
		opword 0xCAC10060
		opword 0xE2A10058
		opword 0xCAA10050
		opword 0xBA210014
		opword 0x80010104
		opword 0x7C0803A6
		opword 0x38210100
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

#pragma pop

#ifdef NONMATCHING
USER_FUNC(evt_eff_softdelete) {
#endif
#ifndef NONMATCHING
s32 evt_eff_softdelete(EventEntry* event, BOOL isFirstCall) {
#endif
	effSoftDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_eff_delete) {
#endif
#ifndef NONMATCHING
s32 evt_eff_delete(EventEntry* event, BOOL isFirstCall) {
#endif
	effDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_eff_softdelete_ptr) {
#endif
#ifndef NONMATCHING
s32 evt_eff_softdelete_ptr(EventEntry* event, BOOL isFirstCall) {
#endif
	effSoftDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

#ifdef NONMATCHING
USER_FUNC(evt_eff_delete_ptr) {
#endif
#ifndef NONMATCHING
s32 evt_eff_delete_ptr(EventEntry* event, BOOL isFirstCall) {
#endif
	effDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

extern void* marioGetPtr(void);
extern s32 marioGetPartyId(void);
extern s32 marioGetExtraPartyId(void);
extern void* partyGetPtr(s32 id);
extern EffectEntry* effFukidashiEntry(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, f32 w, f32 e);

#pragma push
#pragma opt_propagation off
#ifdef NONMATCHING
USER_FUNC(evt_eff_fukidashi) {
	s32* args = event->args;
	s32 mode = evtGetValue(event, args[0]);
	const char* effName = (const char*)evtGetValue(event, args[1]);
	const char* npcName = (const char*)evtGetValue(event, args[2]);
	s32 a = evtGetValue(event, args[3]);
	s32 b = evtGetValue(event, args[4]);
	f32 x = evtGetFloat(event, args[5]);
	f32 y = evtGetFloat(event, args[6]);
	f32 z = evtGetFloat(event, args[7]);
	f32 w = evtGetFloat(event, args[8]);
	f32 e = evtGetFloat(event, args[9]);
	s32 d = evtGetValue(event, args[10]);
	EffectEntry* entry = NULL;
	void* p;
	f32 h;
	f32 zz;

	switch (mode) {
		case 0:
			h = *(f32*)((u8*)marioGetPtr() + 0x1b8);
			{ f32 yy = 2.0f * h / 3.0f; f32 ww = h / 3.0f; entry = effFukidashiEntry(a, b, -1, d, 0.0f, yy, 0.0f, ww, e); }
			break;
		case 1:
			p = !strcmp(npcName, "me") ? (void*)event->ownerNPC : (void*)npcNameToPtr(npcName);
			{ f32 yy = 2.0f * *(f32*)((u8*)p + 0x150) / 3.0f; f32 ww = *(f32*)((u8*)p + 0x150) / 3.0f; entry = effFukidashiEntry(a, b, (s32)p, d, 0.0f, yy, 0.0f, ww, e); }
			break;
		case 2:
			entry = effFukidashiEntry(a, b, 0, d, x, y, z, w, e);
			break;
		case 3:
			p = partyGetPtr(marioGetPartyId());
			if (p) {
				h = *(f32*)((u8*)p + 0xf0);
				{ f32 yy = 2.0f * h / 3.0f; f32 ww = h / 3.0f; entry = effFukidashiEntry(a, b, -2, d, 0.0f, yy, 0.0f, ww, e); }
			}
			break;
		case 4:
			p = partyGetPtr(marioGetExtraPartyId());
			if (p) {
				h = *(f32*)((u8*)p + 0xf0);
				{ f32 yy = 2.0f * h / 3.0f; f32 ww = h / 3.0f; entry = effFukidashiEntry(a, b, -3, d, 0.0f, yy, 0.0f, ww, e); }
			}
			break;
#endif
#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall) {
	asm volatile {
		opword 0x9421FF80
		opword 0x7C0802A6
		opword 0x90010084
		opword 0xDBE10070
		opword 0xF3E10078
		opword 0xDBC10060
		opword 0xF3C10068
		opword 0xDBA10050
		opword 0xF3A10058
		opword 0xDB810040
		opword 0xF3810048
		opword 0xDB610030
		opword 0xF3610038
		opword 0xBF010010
		opword 0x7C781B78
		opword 0x83C30018
		opword 0x809E0000
		bl evtGetValue
		opword 0x809E0004
		opword 0x7C7F1B78
		opword 0x7F03C378
		bl evtGetValue
		opword 0x809E0008
		opword 0x7C7D1B78
		opword 0x7F03C378
		bl evtGetValue
		opword 0x809E000C
		opword 0x7C7C1B78
		opword 0x7F03C378
		bl evtGetValue
		opword 0x809E0010
		opword 0x7C7B1B78
		opword 0x7F03C378
		bl evtGetValue
		opword 0x809E0014
		opword 0x7C7A1B78
		opword 0x7F03C378
		bl evtGetFloat
		opword 0xFFE00890
		opword 0x809E0018
		opword 0x7F03C378
		bl evtGetFloat
		opword 0xFFC00890
		opword 0x809E001C
		opword 0x7F03C378
		bl evtGetFloat
		opword 0xFFA00890
		opword 0x809E0020
		opword 0x7F03C378
		bl evtGetFloat
		opword 0xFF800890
		opword 0x809E0024
		opword 0x7F03C378
		bl evtGetFloat
		opword 0xFF600890
		opword 0x809E0028
		opword 0x7F03C378
		bl evtGetValue
		opword 0x2C1F0002
		opword 0x7C7E1B78
		opword 0x3B200000
		opword 0x418200D0
		opword 0x40800014
		opword 0x2C1F0000
		opword 0x4182001C
		opword 0x4080005C
		opword 0x48000188
		opword 0x2C1F0004
		opword 0x41820134
		opword 0x4080017C
		opword 0x480000DC
		bl marioGetPtr
		opword 0xC06301B8
		opword 0xFCA0D890
		lfs f1, float_2_8041a238(r2)
		opword 0x7F63DB78
		lfs f0, float_3_8041a23c(r2)
		opword 0x7F44D378
		opword 0xEC4100F2
		opword 0xEC830024
		lfs f1, float_0_8041a240(r2)
		opword 0x7FC6F378
		opword 0x38A0FFFF
		opword 0xEC420024
		opword 0xFC600890
		bl effFukidashiEntry
		opword 0x7C791B78
		opword 0x48000134
		opword 0x7F83E378
		la r4, str_8041A244(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x4082000C
		opword 0x80B80170
		opword 0x48000010
		opword 0x7F83E378
		bl npcNameToPtr
		opword 0x7C651B78
		lfs f1, float_2_8041a238(r2)
		opword 0xFCA0D890
		opword 0xC0650150
		opword 0x7F63DB78
		lfs f0, float_3_8041a23c(r2)
		opword 0x7F44D378
		opword 0xEC4100F2
		opword 0xEC830024
		lfs f1, float_0_8041a240(r2)
		opword 0x7FC6F378
		opword 0xEC420024
		opword 0xFC600890
		bl effFukidashiEntry
		opword 0x7C791B78
		opword 0x480000D0
		opword 0xFC20F890
		opword 0x7F63DB78
		opword 0xFC40F090
		opword 0x7F44D378
		opword 0xFC60E890
		opword 0x7FC6F378
		opword 0xFC80E090
		opword 0x38A00000
		opword 0xFCA0D890
		bl effFukidashiEntry
		opword 0x7C791B78
		opword 0x480000A0
		bl marioGetPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820090
		opword 0xC06300F0
		opword 0xFCA0D890
		lfs f1, float_2_8041a238(r2)
		opword 0x7F63DB78
		lfs f0, float_3_8041a23c(r2)
		opword 0x7F44D378
		opword 0xEC4100F2
		opword 0xEC830024
		lfs f1, float_0_8041a240(r2)
		opword 0x7FC6F378
		opword 0x38A0FFFE
		opword 0xEC420024
		opword 0xFC600890
		bl effFukidashiEntry
		opword 0x7C791B78
		opword 0x48000050
		bl marioGetExtraPartyId
		bl partyGetPtr
		opword 0x28030000
		opword 0x41820040
		opword 0xC06300F0
		opword 0xFCA0D890
		lfs f1, float_2_8041a238(r2)
		opword 0x7F63DB78
		lfs f0, float_3_8041a23c(r2)
		opword 0x7F44D378
		opword 0xEC4100F2
		opword 0xEC830024
		lfs f1, float_0_8041a240(r2)
		opword 0x7FC6F378
		opword 0x38A0FFFD
		opword 0xEC420024
		opword 0xFC600890
		bl effFukidashiEntry
		opword 0x7C791B78
		opword 0x281D0000
		opword 0x4182002C
		opword 0x7FA3EB78
		la r4, lbl_8041A248(r2)
		bl strcmp
		opword 0x2C030000
		opword 0x41820018
		opword 0x28190000
		opword 0x41820010
		opword 0x7F23CB78
		opword 0x7FA4EB78
		bl effSetName
		opword 0x38600002
		opword 0xE3E10078
		opword 0xCBE10070
		opword 0xE3C10068
		opword 0xCBC10060
		opword 0xE3A10058
		opword 0xCBA10050
		opword 0xE3810048
		opword 0xCB810040
		opword 0xE3610038
		opword 0xCB610030
		opword 0xBB010010
		opword 0x80010084
		opword 0x7C0803A6
		opword 0x38210080
#endif
	}
#ifdef NONMATCHING

	if (effName && strcmp(effName, "") && entry) {
		effSetName(entry, effName);
	}
	return EVT_RETURN_DONE;
#endif
}
#pragma pop
#ifndef NONMATCHING
#pragma pop
#endif

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f64 double_to_int_802c47d8 = 4503601774854144.0;
__declspec(section ".sdata2") const f32 float_2_8041a238 = 2.0f;
__declspec(section ".sdata2") const f32 float_3_8041a23c = 3.0f;
__declspec(section ".sdata2") const f32 float_0_8041a240 = 0.0f;
__declspec(section ".sdata2") const char str_8041A244[4] = "me\0";
__declspec(section ".sdata2") const u32 lbl_8041A248 = 0x00000000;
__declspec(section ".sdata2") const u32 zero_8041a24c = 0x00000000;
#endif

#ifndef NONMATCHING
// jumptables last, as the target emitted them with their functions
__declspec(section ".data") void* jumptable_8030A890[] = {
    (char*)evt_eff64 + 0x284,
    (char*)evt_eff64 + 0x29C,
    (char*)evt_eff64 + 0x2BC,
    (char*)evt_eff64 + 0x2E0,
    (char*)evt_eff64 + 0x2FC,
    (char*)evt_eff64 + 0x320,
    (char*)evt_eff64 + 0x33C,
    (char*)evt_eff64 + 0x358,
    (char*)evt_eff64 + 0x378,
    (char*)evt_eff64 + 0x398,
    (char*)evt_eff64 + 0x3B4,
    (char*)evt_eff64 + 0x3FC,
    (char*)evt_eff64 + 0x41C,
    (char*)evt_eff64 + 0x448,
    (char*)evt_eff64 + 0x46C,
    (char*)evt_eff64 + 0x48C,
    (char*)evt_eff64 + 0x4AC,
    (char*)evt_eff64 + 0x4CC,
    (char*)evt_eff64 + 0x4E8,
    (char*)evt_eff64 + 0x514,
    (char*)evt_eff64 + 0x530,
    (char*)evt_eff64 + 0x550,
    (char*)evt_eff64 + 0x570,
    (char*)evt_eff64 + 0x59C,
    (char*)evt_eff64 + 0x1130,
    (char*)evt_eff64 + 0x5C8,
    (char*)evt_eff64 + 0x5F0,
    (char*)evt_eff64 + 0x61C,
    (char*)evt_eff64 + 0x63C,
    (char*)evt_eff64 + 0x660,
    (char*)evt_eff64 + 0x67C,
    (char*)evt_eff64 + 0x698,
    (char*)evt_eff64 + 0x6BC,
    (char*)evt_eff64 + 0x6E4,
    (char*)evt_eff64 + 0x708,
    (char*)evt_eff64 + 0x724,
    (char*)evt_eff64 + 0x740,
    (char*)evt_eff64 + 0x764,
    (char*)evt_eff64 + 0x788,
    (char*)evt_eff64 + 0x7AC,
    (char*)evt_eff64 + 0x7C8,
    (char*)evt_eff64 + 0x7E4,
    (char*)evt_eff64 + 0x804,
    (char*)evt_eff64 + 0x824,
    (char*)evt_eff64 + 0x848,
    (char*)evt_eff64 + 0x87C,
    (char*)evt_eff64 + 0x8A0,
    (char*)evt_eff64 + 0x8C4,
    (char*)evt_eff64 + 0x8F0,
    (char*)evt_eff64 + 0x910,
    (char*)evt_eff64 + 0x93C,
    (char*)evt_eff64 + 0x960,
    (char*)evt_eff64 + 0x980,
    (char*)evt_eff64 + 0x9A0,
    (char*)evt_eff64 + 0x9C0,
    (char*)evt_eff64 + 0x9E4,
    (char*)evt_eff64 + 0xA08,
    (char*)evt_eff64 + 0xA1C,
    (char*)evt_eff64 + 0xA38,
    (char*)evt_eff64 + 0xA5C,
    (char*)evt_eff64 + 0xA80,
    (char*)evt_eff64 + 0xAA4,
    (char*)evt_eff64 + 0xACC,
    (char*)evt_eff64 + 0xAFC,
    (char*)evt_eff64 + 0xB2C,
    (char*)evt_eff64 + 0xB50,
    (char*)evt_eff64 + 0xB74,
    (char*)evt_eff64 + 0xB90,
    (char*)evt_eff64 + 0xBB4,
    (char*)evt_eff64 + 0xBD8,
    (char*)evt_eff64 + 0xC08,
    (char*)evt_eff64 + 0xC2C,
    (char*)evt_eff64 + 0xC50,
    (char*)evt_eff64 + 0xC74,
    (char*)evt_eff64 + 0xC98,
    (char*)evt_eff64 + 0xCC8,
    (char*)evt_eff64 + 0xCEC,
    (char*)evt_eff64 + 0xD10,
    (char*)evt_eff64 + 0xD34,
    (char*)evt_eff64 + 0xD58,
    (char*)evt_eff64 + 0xD8C,
    (char*)evt_eff64 + 0xDBC,
    (char*)evt_eff64 + 0xDE0,
    (char*)evt_eff64 + 0xE04,
    (char*)evt_eff64 + 0xE28,
    (char*)evt_eff64 + 0xE4C,
    (char*)evt_eff64 + 0xE70,
    (char*)evt_eff64 + 0xE94,
    (char*)evt_eff64 + 0xEC0,
    (char*)evt_eff64 + 0xEE4,
    (char*)evt_eff64 + 0xF1C,
    (char*)evt_eff64 + 0xF40,
    (char*)evt_eff64 + 0xF70,
    (char*)evt_eff64 + 0xF98,
    (char*)evt_eff64 + 0xFC8,
    (char*)evt_eff64 + 0xFF8,
    (char*)evt_eff64 + 0x101C,
    (char*)evt_eff64 + 0x1040,
    (char*)evt_eff64 + 0x1064,
    (char*)evt_eff64 + 0x1088,
    (char*)evt_eff64 + 0x10AC,
    (char*)evt_eff64 + 0x10D0,
    (char*)evt_eff64 + 0x1110,
};
__declspec(section ".data") void* jumptable_8030AA2C[] = {
    (char*)evt_eff + 0x25C,
    (char*)evt_eff + 0x2BC,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x2DC,
    (char*)evt_eff + 0x364,
    (char*)evt_eff + 0x410,
    (char*)evt_eff + 0x738,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x664,
    (char*)evt_eff + 0x2F8,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x5B0,
    (char*)evt_eff + 0x318,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x3A8,
    (char*)evt_eff + 0x3CC,
    (char*)evt_eff + 0x3EC,
    (char*)evt_eff + 0x840,
    (char*)evt_eff + 0x388,
    (char*)evt_eff + 0x88C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x464,
    (char*)evt_eff + 0x550,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x27C,
    (char*)evt_eff + 0x29C,
    (char*)evt_eff + 0x484,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x4BC,
    (char*)evt_eff + 0x4A0,
    (char*)evt_eff + 0x4DC,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x50C,
    (char*)evt_eff + 0x528,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x590,
    (char*)evt_eff + 0x68C,
    (char*)evt_eff + 0x570,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x5CC,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x6E4,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x6A8,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x71C,
    (char*)evt_eff + 0x700,
    (char*)evt_eff + 0x618,
    (char*)evt_eff + 0x7AC,
    (char*)evt_eff + 0x5F0,
    (char*)evt_eff + 0x634,
    (char*)evt_eff + 0x764,
    (char*)evt_eff + 0x784,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x8E0,
    (char*)evt_eff + 0x7EC,
    (char*)evt_eff + 0x7CC,
    (char*)evt_eff + 0x80C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x8C4,
    (char*)evt_eff + 0x864,
    (char*)evt_eff + 0x8A8,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x97C,
    (char*)evt_eff + 0x900,
    (char*)evt_eff + 0x924,
    (char*)evt_eff + 0x940,
    (char*)evt_eff + 0x964,
};

#endif