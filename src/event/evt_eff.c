#include "evt/evt_eff.h"
#include "driver/effdrv.h"
#include "eff/n64/eff_expbom_n64.h"
#include "eff/eff_n64.h"
#include "evt/evt_cmd.h"
#include <string.h>

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
	}

	if (entry && effName) {
		if (strcmp(effName, "")) {
			effSetName(entry, effName);
		}
	}

	return EVT_RETURN_DONE;
}
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
}
#endif

#pragma pop

#ifdef NONMATCHING
USER_FUNC(evt_eff_softdelete) {
	effSoftDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_eff_delete) {
	effDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_eff_softdelete_ptr) {
	effSoftDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}
#endif

#ifdef NONMATCHING
USER_FUNC(evt_eff_delete_ptr) {
	effDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}
#endif

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
	}

	if (effName && strcmp(effName, "") && entry) {
		effSetName(entry, effName);
	}
	return EVT_RETURN_DONE;
}
#endif
#pragma pop

#ifndef NONMATCHING
void evtGetValue();
#endif
#ifndef NONMATCHING
// FAKE (asm stopgap, asmfake.py --whole): evt_eff (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
void jt_8006B830(void);
void jt_8006B848(void);
void jt_8006B868(void);
void jt_8006B88C(void);
void jt_8006B8A8(void);
void jt_8006B8CC(void);
void jt_8006B8E8(void);
void jt_8006B904(void);
void jt_8006B924(void);
void jt_8006B944(void);
void jt_8006B960(void);
void jt_8006B9A8(void);
void jt_8006B9C8(void);
void jt_8006B9F4(void);
void jt_8006BA18(void);
void jt_8006BA38(void);
void jt_8006BA58(void);
void jt_8006BA78(void);
void jt_8006BA94(void);
void jt_8006BAC0(void);
void jt_8006BADC(void);
void jt_8006BAFC(void);
void jt_8006BB1C(void);
void jt_8006BB48(void);
void jt_8006C6DC(void);
void jt_8006BB74(void);
void jt_8006BB9C(void);
void jt_8006BBC8(void);
void jt_8006BBE8(void);
void jt_8006BC0C(void);
void jt_8006BC28(void);
void jt_8006BC44(void);
void jt_8006BC68(void);
void jt_8006BC90(void);
void jt_8006BCB4(void);
void jt_8006BCD0(void);
void jt_8006BCEC(void);
void jt_8006BD10(void);
void jt_8006BD34(void);
void jt_8006BD58(void);
void jt_8006BD74(void);
void jt_8006BD90(void);
void jt_8006BDB0(void);
void jt_8006BDD0(void);
void jt_8006BDF4(void);
void jt_8006BE28(void);
void jt_8006BE4C(void);
void jt_8006BE70(void);
void jt_8006BE9C(void);
void jt_8006BEBC(void);
void jt_8006BEE8(void);
void jt_8006BF0C(void);
void jt_8006BF2C(void);
void jt_8006BF4C(void);
void jt_8006BF6C(void);
void jt_8006BF90(void);
void jt_8006BFB4(void);
void jt_8006BFC8(void);
void jt_8006BFE4(void);
void jt_8006C008(void);
void jt_8006C02C(void);
void jt_8006C050(void);
void jt_8006C078(void);
void jt_8006C0A8(void);
void jt_8006C0D8(void);
void jt_8006C0FC(void);
void jt_8006C120(void);
void jt_8006C13C(void);
void jt_8006C160(void);
void jt_8006C184(void);
void jt_8006C1B4(void);
void jt_8006C1D8(void);
void jt_8006C1FC(void);
void jt_8006C220(void);
void jt_8006C244(void);
void jt_8006C274(void);
void jt_8006C298(void);
void jt_8006C2BC(void);
void jt_8006C2E0(void);
void jt_8006C304(void);
void jt_8006C338(void);
void jt_8006C368(void);
void jt_8006C38C(void);
void jt_8006C3B0(void);
void jt_8006C3D4(void);
void jt_8006C3F8(void);
void jt_8006C41C(void);
void jt_8006C440(void);
void jt_8006C46C(void);
void jt_8006C490(void);
void jt_8006C4C8(void);
void jt_8006C4EC(void);
void jt_8006C51C(void);
void jt_8006C544(void);
void jt_8006C574(void);
void jt_8006C5A4(void);
void jt_8006C5C8(void);
void jt_8006C5EC(void);
void jt_8006C610(void);
void jt_8006C634(void);
void jt_8006C658(void);
void jt_8006C67C(void);
void jt_8006C6BC(void);
__declspec(section ".data") void* jumptable_8030A890[103] = {jt_8006B830, jt_8006B848, jt_8006B868, jt_8006B88C, jt_8006B8A8, jt_8006B8CC, jt_8006B8E8, jt_8006B904, jt_8006B924, jt_8006B944, jt_8006B960, jt_8006B9A8, jt_8006B9C8, jt_8006B9F4, jt_8006BA18, jt_8006BA38, jt_8006BA58, jt_8006BA78, jt_8006BA94, jt_8006BAC0, jt_8006BADC, jt_8006BAFC, jt_8006BB1C, jt_8006BB48, jt_8006C6DC, jt_8006BB74, jt_8006BB9C, jt_8006BBC8, jt_8006BBE8, jt_8006BC0C, jt_8006BC28, jt_8006BC44, jt_8006BC68, jt_8006BC90, jt_8006BCB4, jt_8006BCD0, jt_8006BCEC, jt_8006BD10, jt_8006BD34, jt_8006BD58, jt_8006BD74, jt_8006BD90, jt_8006BDB0, jt_8006BDD0, jt_8006BDF4, jt_8006BE28, jt_8006BE4C, jt_8006BE70, jt_8006BE9C, jt_8006BEBC, jt_8006BEE8, jt_8006BF0C, jt_8006BF2C, jt_8006BF4C, jt_8006BF6C, jt_8006BF90, jt_8006BFB4, jt_8006BFC8, jt_8006BFE4, jt_8006C008, jt_8006C02C, jt_8006C050, jt_8006C078, jt_8006C0A8, jt_8006C0D8, jt_8006C0FC, jt_8006C120, jt_8006C13C, jt_8006C160, jt_8006C184, jt_8006C1B4, jt_8006C1D8, jt_8006C1FC, jt_8006C220, jt_8006C244, jt_8006C274, jt_8006C298, jt_8006C2BC, jt_8006C2E0, jt_8006C304, jt_8006C338, jt_8006C368, jt_8006C38C, jt_8006C3B0, jt_8006C3D4, jt_8006C3F8, jt_8006C41C, jt_8006C440, jt_8006C46C, jt_8006C490, jt_8006C4C8, jt_8006C4EC, jt_8006C51C, jt_8006C544, jt_8006C574, jt_8006C5A4, jt_8006C5C8, jt_8006C5EC, jt_8006C610, jt_8006C634, jt_8006C658, jt_8006C67C, jt_8006C6BC};
void jt_8006C9D8(void);
void jt_8006CA38(void);
void jt_8006D0F8(void);
void jt_8006CA58(void);
void jt_8006CAE0(void);
void jt_8006CB8C(void);
void jt_8006CEB4(void);
void jt_8006CDE0(void);
void jt_8006CA74(void);
void jt_8006CD2C(void);
void jt_8006CA94(void);
void jt_8006CB24(void);
void jt_8006CB48(void);
void jt_8006CB68(void);
void jt_8006CFBC(void);
void jt_8006CB04(void);
void jt_8006D008(void);
void jt_8006CBE0(void);
void jt_8006CCCC(void);
void jt_8006C9F8(void);
void jt_8006CA18(void);
void jt_8006CC00(void);
void jt_8006CC38(void);
void jt_8006CC1C(void);
void jt_8006CC58(void);
void jt_8006CC88(void);
void jt_8006CCA4(void);
void jt_8006CD0C(void);
void jt_8006CE08(void);
void jt_8006CCEC(void);
void jt_8006CD48(void);
void jt_8006CE60(void);
void jt_8006CE24(void);
void jt_8006CE98(void);
void jt_8006CE7C(void);
void jt_8006CD94(void);
void jt_8006CF28(void);
void jt_8006CD6C(void);
void jt_8006CDB0(void);
void jt_8006CEE0(void);
void jt_8006CF00(void);
void jt_8006D05C(void);
void jt_8006CF68(void);
void jt_8006CF48(void);
void jt_8006CF88(void);
void jt_8006D040(void);
void jt_8006CFE0(void);
void jt_8006D024(void);
void jt_8006D07C(void);
void jt_8006D0A0(void);
void jt_8006D0BC(void);
void jt_8006D0E0(void);
__declspec(section ".data") void* jumptable_8030AA2C[79] = {jt_8006C9D8, jt_8006CA38, jt_8006D0F8, jt_8006CA58, jt_8006CAE0, jt_8006CB8C, jt_8006CEB4, jt_8006D0F8, jt_8006D0F8, jt_8006CDE0, jt_8006CA74, jt_8006D0F8, jt_8006CD2C, jt_8006CA94, jt_8006D0F8, jt_8006D0F8, jt_8006D0F8, jt_8006D0F8, jt_8006CB24, jt_8006CB48, jt_8006CB68, jt_8006CFBC, jt_8006CB04, jt_8006D008, jt_8006D0F8, jt_8006CBE0, jt_8006CCCC, jt_8006D0F8, jt_8006C9F8, jt_8006CA18, jt_8006CC00, jt_8006D0F8, jt_8006D0F8, jt_8006CC38, jt_8006CC1C, jt_8006CC58, jt_8006D0F8, jt_8006D0F8, jt_8006D0F8, jt_8006CC88, jt_8006CCA4, jt_8006D0F8, jt_8006D0F8, jt_8006CD0C, jt_8006CE08, jt_8006CCEC, jt_8006D0F8, jt_8006CD48, jt_8006D0F8, jt_8006D0F8, jt_8006CE60, jt_8006D0F8, jt_8006CE24, jt_8006D0F8, jt_8006CE98, jt_8006CE7C, jt_8006CD94, jt_8006CF28, jt_8006CD6C, jt_8006CDB0, jt_8006CEE0, jt_8006CF00, jt_8006D0F8, jt_8006D05C, jt_8006CF68, jt_8006CF48, jt_8006CF88, jt_8006D0F8, jt_8006D040, jt_8006CFE0, jt_8006D024, jt_8006D0F8, jt_8006D0F8, jt_8006D0F8, jt_8006D0F8, jt_8006D07C, jt_8006D0A0, jt_8006D0BC, jt_8006D0E0};
__declspec(section ".sdata2") const f32 float_2_8041a238 = 2.0f;
__declspec(section ".sdata2") const f32 float_3_8041a23c = 3.0f;
__declspec(section ".sdata2") const f32 float_0_8041a240 = 0.0f;
__declspec(section ".sdata2") const char str_8041A244[4] = "me\0";
__declspec(section ".sdata2") const u32 lbl_8041A248 = 0x00000000;
__declspec(section ".sdata2") const u32 zero_8041a24c = 0x00000000;
#pragma force_active on
__declspec(section ".rodata") const f64 double_to_int_802c47d8 = 4503601774854144;
#pragma force_active reset
USER_FUNC(evt_eff_fukidashi);
USER_FUNC(evt_eff_delete_ptr);
USER_FUNC(evt_eff_softdelete_ptr);
USER_FUNC(evt_eff_delete);
USER_FUNC(evt_eff_softdelete);
s32 evt_eff64(EventEntry *event, BOOL isFirstCall);
USER_FUNC(evt_eff);

asm s32 evt_eff_fukidashi(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x80(r1)
	mflr r0
	stw r0, 0x84(r1)
	stfd f31, 0x70(r1)
	psq_st f31, 0x78(r1), 0, 0
	stfd f30, 0x60(r1)
	psq_st f30, 0x68(r1), 0, 0
	stfd f29, 0x50(r1)
	psq_st f29, 0x58(r1), 0, 0
	stfd f28, 0x40(r1)
	psq_st f28, 0x48(r1), 0, 0
	stfd f27, 0x30(r1)
	psq_st f27, 0x38(r1), 0, 0
	stmw r24, 0x10(r1)
	mr r24, r3
	lwz r30, 0x18(r3)
	lwz r4, 0x0(r30)
	bl evtGetValue
	lwz r4, 0x4(r30)
	mr r31, r3
	mr r3, r24
	bl evtGetValue
	lwz r4, 0x8(r30)
	mr r29, r3
	mr r3, r24
	bl evtGetValue
	lwz r4, 0xc(r30)
	mr r28, r3
	mr r3, r24
	bl evtGetValue
	lwz r4, 0x10(r30)
	mr r27, r3
	mr r3, r24
	bl evtGetValue
	lwz r4, 0x14(r30)
	mr r26, r3
	mr r3, r24
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x18(r30)
	mr r3, r24
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x1c(r30)
	mr r3, r24
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x20(r30)
	mr r3, r24
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x24(r30)
	mr r3, r24
	bl evtGetFloat
	fmr f27, f1
	lwz r4, 0x28(r30)
	mr r3, r24
	bl evtGetValue
	cmpwi r31, 0x2
	mr r30, r3
	li r25, 0x0
	beq @1
	bge @2
	cmpwi r31, 0x0
	beq @3
	bge @4
	b @5
	@2:
	cmpwi r31, 0x4
	beq @6
	bge @5
	b @7
	@3:
	bl marioGetPtr
	lfs f3, 0x1b8(r3)
	fmr f5, f27
	lfs f1, float_2_8041a238(r2)
	mr r3, r27
	lfs f0, float_3_8041a23c(r2)
	mr r4, r26
	fmuls f2, f1, f3
	fdivs f4, f3, f0
	lfs f1, float_0_8041a240(r2)
	mr r6, r30
	li r5, -0x1
	fdivs f2, f2, f0
	fmr f3, f1
	bl effFukidashiEntry
	mr r25, r3
	b @5
	@4:
	mr r3, r28
	la r4, str_8041A244(r2)
	bl strcmp
	cmpwi r3, 0x0
	bne @8
	lwz r5, 0x170(r24)
	b @9
	@8:
	mr r3, r28
	bl npcNameToPtr
	mr r5, r3
	@9:
	lfs f1, float_2_8041a238(r2)
	fmr f5, f27
	lfs f3, 0x150(r5)
	mr r3, r27
	lfs f0, float_3_8041a23c(r2)
	mr r4, r26
	fmuls f2, f1, f3
	fdivs f4, f3, f0
	lfs f1, float_0_8041a240(r2)
	mr r6, r30
	fdivs f2, f2, f0
	fmr f3, f1
	bl effFukidashiEntry
	mr r25, r3
	b @5
	@1:
	fmr f1, f31
	mr r3, r27
	fmr f2, f30
	mr r4, r26
	fmr f3, f29
	mr r6, r30
	fmr f4, f28
	li r5, 0x0
	fmr f5, f27
	bl effFukidashiEntry
	mr r25, r3
	b @5
	@7:
	bl marioGetPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @5
	lfs f3, 0xf0(r3)
	fmr f5, f27
	lfs f1, float_2_8041a238(r2)
	mr r3, r27
	lfs f0, float_3_8041a23c(r2)
	mr r4, r26
	fmuls f2, f1, f3
	fdivs f4, f3, f0
	lfs f1, float_0_8041a240(r2)
	mr r6, r30
	li r5, -0x2
	fdivs f2, f2, f0
	fmr f3, f1
	bl effFukidashiEntry
	mr r25, r3
	b @5
	@6:
	bl marioGetExtraPartyId
	bl partyGetPtr
	cmplwi r3, 0x0
	beq @5
	lfs f3, 0xf0(r3)
	fmr f5, f27
	lfs f1, float_2_8041a238(r2)
	mr r3, r27
	lfs f0, float_3_8041a23c(r2)
	mr r4, r26
	fmuls f2, f1, f3
	fdivs f4, f3, f0
	lfs f1, float_0_8041a240(r2)
	mr r6, r30
	li r5, -0x3
	fdivs f2, f2, f0
	fmr f3, f1
	bl effFukidashiEntry
	mr r25, r3
	@5:
	cmplwi r29, 0x0
	beq @10
	mr r3, r29
	la r4, lbl_8041A248(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @10
	cmplwi r25, 0x0
	beq @10
	mr r3, r25
	mr r4, r29
	bl effSetName
	@10:
	li r3, 0x2
	psq_l f31, 0x78(r1), 0, 0
	lfd f31, 0x70(r1)
	psq_l f30, 0x68(r1), 0, 0
	lfd f30, 0x60(r1)
	psq_l f29, 0x58(r1), 0, 0
	lfd f29, 0x50(r1)
	psq_l f28, 0x48(r1), 0, 0
	lfd f28, 0x40(r1)
	psq_l f27, 0x38(r1), 0, 0
	lfd f27, 0x30(r1)
	lmw r24, 0x10(r1)
	lwz r0, 0x84(r1)
	mtlr r0
	addi r1, r1, 0x80
	blr
}

asm s32 evt_eff_delete_ptr(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl effDelete
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_eff_softdelete_ptr(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl effSoftDelete
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_eff_delete(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl effNameToPtr
	bl effDelete
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_eff_softdelete(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r4, 0x18(r3)
	lwz r4, 0x0(r4)
	bl evtGetValue
	bl effNameToPtr
	bl effSoftDelete
	lwz r0, 0x14(r1)
	li r3, 0x2
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 evt_eff64(EventEntry *event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stfd f29, 0xd0(r1)
	psq_st f29, 0xd8(r1), 0, 0
	stfd f28, 0xc0(r1)
	psq_st f28, 0xc8(r1), 0, 0
	stfd f27, 0xb0(r1)
	psq_st f27, 0xb8(r1), 0, 0
	stfd f26, 0xa0(r1)
	psq_st f26, 0xa8(r1), 0, 0
	stfd f25, 0x90(r1)
	psq_st f25, 0x98(r1), 0, 0
	stfd f24, 0x80(r1)
	psq_st f24, 0x88(r1), 0, 0
	stfd f23, 0x70(r1)
	psq_st f23, 0x78(r1), 0, 0
	stfd f22, 0x60(r1)
	psq_st f22, 0x68(r1), 0, 0
	stfd f21, 0x50(r1)
	psq_st f21, 0x58(r1), 0, 0
	stmw r17, 0x14(r1)
	mr r30, r3
	lwz r17, 0x18(r3)
	lwz r4, 0x0(r17)
	bl evtGetValue
	lwz r4, 0x0(r17)
	mr r31, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x0(r17)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x4(r17)
	mr r3, r30
	addi r29, r17, 0x8
	bl evtGetValue
	lwz r4, 0x4(r17)
	mr r26, r3
	mr r3, r30
	mr r28, r29
	bl evtGetValue
	lwz r4, 0x4(r17)
	mr r3, r30
	mr r27, r29
	bl evtGetValue
	lwz r4, 0x0(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x4(r29)
	mr r25, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x8(r29)
	mr r24, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0xc(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x10(r29)
	mr r23, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x14(r29)
	mr r22, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x18(r29)
	mr r21, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x1c(r29)
	mr r20, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x20(r29)
	mr r19, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x24(r29)
	mr r18, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x28(r29)
	mr r17, r3
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x2c(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x30(r29)
	mr r3, r30
	bl evtGetValue
	lwz r4, 0x0(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x4(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x8(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0xc(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0x10(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f27, f1
	lwz r4, 0x14(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f26, f1
	lwz r4, 0x18(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f25, f1
	lwz r4, 0x1c(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f24, f1
	lwz r4, 0x20(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f23, f1
	lwz r4, 0x24(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f22, f1
	lwz r4, 0x28(r28)
	mr r3, r30
	bl evtGetFloat
	fmr f21, f1
	lwz r4, 0x2c(r28)
	mr r3, r30
	bl evtGetFloat
	lwz r4, 0x30(r28)
	mr r3, r30
	bl evtGetFloat
	lwz r27, 0x4(r27)
	mr r3, r26
	li r26, 0x0
	bl effGetSetN64
	lha r0, 0x0(r3)
	cmplwi r0, 0x66
	bgt @1
	lis r3, jumptable_8030A890@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8030A890@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@2:
	entry jt_8006B830
	fmr f1, f31
	fmr f2, f30
	fmr f3, f29
	bl effExpBomN64Entry
	mr r26, r3
	b @1
	@3:
	entry jt_8006B848
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effKemuri1N64Entry
	mr r26, r3
	b @1
	@4:
	entry jt_8006B868
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effKemuri2N64Entry
	mr r26, r3
	b @1
	@5:
	entry jt_8006B88C
	fmr f1, f31
	fmr f2, f30
	fmr f3, f29
	fmr f4, f28
	bl effKemuri3N64Entry
	mr r26, r3
	b @1
	@6:
	entry jt_8006B8A8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effKemuri4N64Entry
	mr r26, r3
	b @1
	@7:
	entry jt_8006B8CC
	fmr f1, f31
	fmr f2, f30
	fmr f3, f29
	fmr f4, f28
	bl effKemuri5N64Entry
	mr r26, r3
	b @1
	@8:
	entry jt_8006B8E8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effKemuri6N64Entry
	mr r26, r3
	b @1
	@9:
	entry jt_8006B904
	fmr f1, f31
	fmr f2, f30
	fmr f3, f29
	fmr f4, f28
	fmr f5, f27
	bl effKemuri7N64Entry
	mr r26, r3
	b @1
	@10:
	entry jt_8006B924
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effFlowerN64Entry
	mr r26, r3
	b @1
	@11:
	entry jt_8006B944
	fmr f1, f31
	mr r3, r23
	fmr f2, f30
	fmr f3, f28
	bl effSnowN64Entry
	mr r26, r3
	b @1
	@12:
	entry jt_8006B960
	xoris r3, r19, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_802c47d8@ha
	lfd f7, double_to_int_802c47d8@l(r4)
	fmr f1, f30
	stw r0, 0x8(r1)
	fmr f2, f29
	fmr f3, f28
	mr r3, r25
	lfd f0, 0x8(r1)
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fsubs f7, f0, f7
	bl effSstarN64Entry
	mr r26, r3
	b @1
	@13:
	entry jt_8006B9A8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effStardustN64Entry
	mr r26, r3
	b @1
	@14:
	entry jt_8006B9C8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	bl effMagic1N64Entry
	mr r26, r3
	b @1
	@15:
	entry jt_8006B9F4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effMagic2N64Entry
	mr r26, r3
	b @1
	@16:
	entry jt_8006BA18
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effFallLeafN64Entry
	mr r26, r3
	b @1
	@17:
	entry jt_8006BA38
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effHokoriN64Entry
	mr r26, r3
	b @1
	@18:
	entry jt_8006BA58
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effGarekiN64Entry
	mr r26, r3
	b @1
	@19:
	entry jt_8006BA78
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effKemuri8N64Entry
	mr r26, r3
	b @1
	@20:
	entry jt_8006BA94
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	bl effSmallStarN64Entry
	mr r26, r3
	b @1
	@21:
	entry jt_8006BAC0
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effBombN64Entry
	mr r26, r3
	b @1
	@22:
	entry jt_8006BADC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effWangFlushN64Entry
	mr r26, r3
	b @1
	@23:
	entry jt_8006BAFC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effMagic3N64Entry
	mr r26, r3
	b @1
	@24:
	entry jt_8006BB1C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	mr r5, r19
	fmr f4, f27
	fmr f5, f25
	bl effKemuri9N64Entry
	mr r26, r3
	b @1
	@25:
	entry jt_8006BB48
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effKemuri10N64Entry
	mr r26, r3
	b @1
	@26:
	entry jt_8006BB74
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r20
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effRappaN64Entry
	mr r26, r3
	b @1
	@27:
	entry jt_8006BB9C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r20
	fmr f3, f28
	mr r5, r19
	fmr f4, f27
	fmr f5, f26
	bl effStardust2N64Entry
	mr r26, r3
	b @1
	@28:
	entry jt_8006BBC8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effRippleN64Entry
	mr r26, r3
	b @1
	@29:
	entry jt_8006BBE8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effExplosionN64Entry
	mr r26, r3
	b @1
	@30:
	entry jt_8006BC0C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effKemuri11N64Entry
	mr r26, r3
	b @1
	@31:
	entry jt_8006BC28
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effOnpuN64Entry
	mr r26, r3
	b @1
	@32:
	entry jt_8006BC44
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effKemuri12N64Entry
	mr r26, r3
	b @1
	@33:
	entry jt_8006BC68
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r20
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effSweatN64Entry
	mr r26, r3
	b @1
	@34:
	entry jt_8006BC90
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effBalloonN64Entry
	mr r26, r3
	b @1
	@35:
	entry jt_8006BCB4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effCoolLeafN64Entry
	mr r26, r3
	b @1
	@36:
	entry jt_8006BCD0
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effBushN64Entry
	mr r26, r3
	b @1
	@37:
	entry jt_8006BCEC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	mr r5, r21
	bl effRotHammerSuccessN64Entry
	mr r26, r3
	b @1
	@38:
	entry jt_8006BD10
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effRotHammerFailN64Entry
	mr r26, r3
	b @1
	@39:
	entry jt_8006BD34
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effGuruguruN64Entry
	mr r26, r3
	b @1
	@40:
	entry jt_8006BD58
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effIceN64Entry
	mr r26, r3
	b @1
	@41:
	entry jt_8006BD74
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effStampN64Entry
	mr r26, r3
	b @1
	@42:
	entry jt_8006BD90
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effThruHammerN64Entry
	mr r26, r3
	b @1
	@43:
	entry jt_8006BDB0
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effRadiationN64Entry
	mr r26, r3
	b @1
	@44:
	entry jt_8006BDD0
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effThunderN64Entry
	mr r26, r3
	b @1
	@45:
	entry jt_8006BDF4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	mr r5, r18
	fmr f4, f27
	mr r6, r17
	fmr f5, f26
	fmr f6, f25
	bl effBreathFireN64Entry
	mr r26, r3
	b @1
	@46:
	entry jt_8006BE28
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effBrokenBarrierN64Entry
	mr r26, r3
	b @1
	@47:
	entry jt_8006BE4C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effFireRingN64Entry
	mr r26, r3
	b @1
	@48:
	entry jt_8006BE70
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r20
	fmr f3, f28
	mr r5, r19
	fmr f4, f27
	fmr f5, f26
	bl effFireDustN64Entry
	mr r26, r3
	b @1
	@49:
	entry jt_8006BE9C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	bl effFlameN64Entry
	mr r26, r3
	b @1
	@50:
	entry jt_8006BEBC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	bl effBlowN64Entry
	mr r26, r3
	b @1
	@51:
	entry jt_8006BEE8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effBomheiN64Entry
	mr r26, r3
	b @1
	@52:
	entry jt_8006BF0C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effFireFlowerN64Entry
	mr r26, r3
	b @1
	@53:
	entry jt_8006BF2C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effRecoverHeartN64Entry
	mr r26, r3
	b @1
	@54:
	entry jt_8006BF4C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r22
	fmr f3, f28
	bl effPturnN64Entry
	mr r26, r3
	b @1
	@55:
	entry jt_8006BF6C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effHitN64Entry
	mr r26, r3
	b @1
	@56:
	entry jt_8006BF90
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effConfettiN64Entry
	mr r26, r3
	b @1
	@57:
	entry jt_8006BFB4
	mr r3, r25
	mr r4, r24
	bl effSnowfallN64Entry
	mr r26, r3
	b @1
	@58:
	entry jt_8006BFC8
	fmr f1, f29
	mr r3, r25
	mr r4, r27
	mr r5, r23
	bl effWhirlwindN64Entry
	mr r26, r3
	b @1
	@59:
	entry jt_8006BFE4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effThunderflareN64Entry
	mr r26, r3
	b @1
	@60:
	entry jt_8006C008
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effCoinN64Entry
	mr r26, r3
	b @1
	@61:
	entry jt_8006C02C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effShockN64Entry
	mr r26, r3
	b @1
	@62:
	entry jt_8006C050
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r20
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	bl effBalloonHeihoN64Entry
	mr r26, r3
	b @1
	@63:
	entry jt_8006C078
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r18
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effRubbleN64Entry
	mr r26, r3
	b @1
	@64:
	entry jt_8006C0A8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	mr r5, r19
	fmr f4, f27
	mr r6, r17
	fmr f5, f25
	fmr f6, f23
	bl effMagicHoraoN64Entry
	b @1
	@65:
	entry jt_8006C0D8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effLensflareN64Entry
	mr r26, r3
	b @1
	@66:
	entry jt_8006C0FC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effCrystalN64Entry
	mr r26, r3
	b @1
	@67:
	entry jt_8006C120
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	bl effButterflyN64Entry
	mr r26, r3
	b @1
	@68:
	entry jt_8006C13C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effAkariChargeN64Entry
	mr r26, r3
	b @1
	@69:
	entry jt_8006C160
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effAkariSflushN64Entry
	mr r26, r3
	b @1
	@70:
	entry jt_8006C184
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r18
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effOpukuWgunN64Entry
	mr r26, r3
	b @1
	@71:
	entry jt_8006C1B4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effOpukuWprotectN64Entry
	mr r26, r3
	b @1
	@72:
	entry jt_8006C1D8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effOpukuWcurtainN64Entry
	mr r26, r3
	b @1
	@73:
	entry jt_8006C1FC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effOpukuJetwN64Entry
	mr r26, r3
	b @1
	@74:
	entry jt_8006C220
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effOpukuJetwrainN64Entry
	mr r26, r3
	b @1
	@75:
	entry jt_8006C244
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r18
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effPokopiThunderN64Entry
	mr r26, r3
	b @1
	@76:
	entry jt_8006C274
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effWaterDamageN64Entry
	mr r26, r3
	b @1
	@77:
	entry jt_8006C298
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effSnowmanN64Entry
	mr r26, r3
	b @1
	@78:
	entry jt_8006C2BC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effHolographyN64Entry
	mr r26, r3
	b @1
	@79:
	entry jt_8006C2E0
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effTimestampN64Entry
	mr r26, r3
	b @1
	@80:
	entry jt_8006C304
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r18
	fmr f3, f28
	mr r5, r17
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effPacknBfireN64Entry
	mr r26, r3
	b @1
	@81:
	entry jt_8006C338
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r18
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effPokopiPipoN64Entry
	mr r26, r3
	b @1
	@82:
	entry jt_8006C368
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effCloudN64Entry
	mr r26, r3
	b @1
	@83:
	entry jt_8006C38C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effDogabonAttackN64Entry
	mr r26, r3
	b @1
	@84:
	entry jt_8006C3B0
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effKamekiTornadeN64Entry
	mr r26, r3
	b @1
	@85:
	entry jt_8006C3D4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effStoneSmokeN64Entry
	mr r26, r3
	b @1
	@86:
	entry jt_8006C3F8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effPokopiPchargeN64Entry
	mr r26, r3
	b @1
	@87:
	entry jt_8006C41C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effHagetakaFlushN64Entry
	mr r26, r3
	b @1
	@88:
	entry jt_8006C440
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	bl effKumokumoN64Entry
	mr r26, r3
	b @1
	@89:
	entry jt_8006C46C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effVaporN64Entry
	mr r26, r3
	b @1
	@90:
	entry jt_8006C490
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	mr r5, r18
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f22
	fmr f8, f21
	bl effFireSparkN64Entry
	mr r26, r3
	b @1
	@91:
	entry jt_8006C4C8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effHoraoSpellN64Entry
	mr r26, r3
	b @1
	@92:
	entry jt_8006C4EC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r19
	fmr f3, f28
	mr r5, r18
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	bl effSnowDustN64Entry
	mr r26, r3
	b @1
	@93:
	entry jt_8006C51C
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	mr r5, r20
	fmr f4, f27
	bl effAkariPoseN64Entry
	mr r26, r3
	b @1
	@94:
	entry jt_8006C544
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	fmr f8, f23
	bl effKumokumoChipN64Entry
	mr r26, r3
	b @1
	@95:
	entry jt_8006C574
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r18
	fmr f3, f28
	fmr f4, f27
	fmr f5, f26
	fmr f6, f25
	fmr f7, f24
	bl effFireworksN64Entry
	mr r26, r3
	b @1
	@96:
	entry jt_8006C5A4
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effGlassN64Entry
	mr r26, r3
	b @1
	@97:
	entry jt_8006C5C8
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effBoobooN64Entry
	mr r26, r3
	b @1
	@98:
	entry jt_8006C5EC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effPikkyoloN64Entry
	mr r26, r3
	b @1
	@99:
	entry jt_8006C610
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effFreezeN64Entry
	mr r26, r3
	b @1
	@100:
	entry jt_8006C634
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effSunlightN64Entry
	mr r26, r3
	b @1
	@101:
	entry jt_8006C658
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effReleaseN64Entry
	mr r26, r3
	b @1
	@102:
	entry jt_8006C67C
	xoris r3, r21, 0x8000
	lis r0, 0x4330
	stw r3, 0xc(r1)
	lis r4, double_to_int_802c47d8@ha
	lfd f5, double_to_int_802c47d8@l(r4)
	fmr f1, f30
	stw r0, 0x8(r1)
	fmr f2, f29
	fmr f3, f28
	mr r3, r25
	lfd f0, 0x8(r1)
	fmr f4, f27
	fsubs f5, f0, f5
	bl effPeachDustN64Entry
	mr r26, r3
	b @1
	@103:
	entry jt_8006C6BC
	fmr f1, f30
	mr r3, r25
	fmr f2, f29
	mr r4, r21
	fmr f3, f28
	fmr f4, f27
	bl effStarPowerN64Entry
	mr r26, r3
	@1:
	entry jt_8006C6DC
	cmplwi r26, 0x0
	beq @104
	cmplwi r31, 0x0
	beq @104
	mr r3, r31
	la r4, lbl_8041A248(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @104
	mr r3, r26
	mr r4, r31
	bl effSetName
	@104:
	li r3, 0x2
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	psq_l f29, 0xd8(r1), 0, 0
	lfd f29, 0xd0(r1)
	psq_l f28, 0xc8(r1), 0, 0
	lfd f28, 0xc0(r1)
	psq_l f27, 0xb8(r1), 0, 0
	lfd f27, 0xb0(r1)
	psq_l f26, 0xa8(r1), 0, 0
	lfd f26, 0xa0(r1)
	psq_l f25, 0x98(r1), 0, 0
	lfd f25, 0x90(r1)
	psq_l f24, 0x88(r1), 0, 0
	lfd f24, 0x80(r1)
	psq_l f23, 0x78(r1), 0, 0
	lfd f23, 0x70(r1)
	psq_l f22, 0x68(r1), 0, 0
	lfd f22, 0x60(r1)
	psq_l f21, 0x58(r1), 0, 0
	lfd f21, 0x50(r1)
	lmw r17, 0x14(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm s32 evt_eff(EventEntry* event, BOOL isFirstCall) {
	nofralloc
	stwu r1, -0xe0(r1)
	mflr r0
	stw r0, 0xe4(r1)
	stfd f31, 0xd0(r1)
	psq_st f31, 0xd8(r1), 0, 0
	stfd f30, 0xc0(r1)
	psq_st f30, 0xc8(r1), 0, 0
	stfd f29, 0xb0(r1)
	psq_st f29, 0xb8(r1), 0, 0
	stfd f28, 0xa0(r1)
	psq_st f28, 0xa8(r1), 0, 0
	stfd f27, 0x90(r1)
	psq_st f27, 0x98(r1), 0, 0
	stfd f26, 0x80(r1)
	psq_st f26, 0x88(r1), 0, 0
	stfd f25, 0x70(r1)
	psq_st f25, 0x78(r1), 0, 0
	stfd f24, 0x60(r1)
	psq_st f24, 0x68(r1), 0, 0
	stfd f23, 0x50(r1)
	psq_st f23, 0x58(r1), 0, 0
	stmw r20, 0x20(r1)
	mr r26, r3
	lwz r27, 0x18(r3)
	lwz r4, 0x0(r27)
	bl evtGetValue
	lwz r4, 0x0(r27)
	mr r31, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x0(r27)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r3, r26
	addi r25, r27, 0x8
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r23, r3
	mr r3, r26
	mr r24, r25
	bl evtGetValue
	lwz r4, 0x4(r27)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x0(r25)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x4(r25)
	mr r30, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x8(r25)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0xc(r25)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x10(r25)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x14(r25)
	mr r29, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x18(r25)
	mr r28, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x1c(r25)
	mr r27, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x20(r25)
	mr r22, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x24(r25)
	mr r21, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x28(r25)
	mr r20, r3
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x2c(r25)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x30(r25)
	mr r3, r26
	bl evtGetValue
	lwz r4, 0x0(r24)
	mr r3, r26
	bl evtGetFloat
	lwz r4, 0x4(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f29, f1
	lwz r4, 0x8(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f28, f1
	lwz r4, 0xc(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f27, f1
	lwz r4, 0x10(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f26, f1
	lwz r4, 0x14(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f25, f1
	lwz r4, 0x18(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f24, f1
	lwz r4, 0x1c(r24)
	mr r3, r26
	bl evtGetFloat
	lwz r4, 0x20(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f23, f1
	lwz r4, 0x24(r24)
	mr r3, r26
	bl evtGetFloat
	lwz r4, 0x28(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f30, f1
	lwz r4, 0x2c(r24)
	mr r3, r26
	bl evtGetFloat
	fmr f31, f1
	lwz r4, 0x30(r24)
	mr r3, r26
	bl evtGetFloat
	mr r3, r23
	li r23, 0x0
	bl effGetSet
	lha r0, 0x0(r3)
	cmplwi r0, 0x4e
	bgt @1
	lis r3, jumptable_8030AA2C@ha
	slwi r0, r0, 2
	addi r3, r3, jumptable_8030AA2C@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	@2:
	entry jt_8006C9D8
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effKemuriEntry
	mr r23, r3
	b @1
	@3:
	entry jt_8006C9F8
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effKemuTestEntry
	mr r23, r3
	b @1
	@4:
	entry jt_8006CA18
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effStarStoneEntry
	mr r23, r3
	b @1
	@5:
	entry jt_8006CA38
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effConfettiEntry
	mr r23, r3
	b @1
	@6:
	entry jt_8006CA58
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effButterflyEntry
	mr r23, r3
	b @1
	@7:
	entry jt_8006CA74
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effRecoveryEntry
	mr r23, r3
	b @1
	@8:
	entry jt_8006CA94
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r22
	fmr f3, f27
	mr r5, r21
	fmr f4, f26
	mr r6, r20
	fmr f5, f25
	fmr f6, f24
	bl effBreathFireEntry
	mr r23, r3
	lwz r3, 0xc(r3)
	stfs f30, 0x38(r3)
	lwz r3, 0xc(r23)
	stfs f30, 0x30(r3)
	lwz r3, 0xc(r23)
	stfs f31, 0x34(r3)
	b @1
	@9:
	entry jt_8006CAE0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effHitEntry
	mr r23, r3
	b @1
	@10:
	entry jt_8006CB04
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effBombEntry
	mr r23, r3
	b @1
	@11:
	entry jt_8006CB24
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effChargeEntry
	mr r23, r3
	b @1
	@12:
	entry jt_8006CB48
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effTogeFlushEntry
	mr r23, r3
	b @1
	@13:
	entry jt_8006CB68
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effIceEntry
	mr r23, r3
	b @1
	@14:
	entry jt_8006CB8C
	lis r5, 0x4330
	xoris r3, r29, 0x8000
	stw r3, 0xc(r1)
	xoris r0, r28, 0x8000
	lis r4, double_to_int_802c47d8@ha
	fmr f1, f29
	stw r5, 0x8(r1)
	fmr f2, f28
	lfd f5, double_to_int_802c47d8@l(r4)
	fmr f3, f27
	lfd f0, 0x8(r1)
	stw r0, 0x14(r1)
	mr r3, r30
	fsubs f4, f0, f5
	mr r4, r27
	stw r5, 0x10(r1)
	lfd f0, 0x10(r1)
	fsubs f5, f0, f5
	bl effDamageStarEntry
	mr r23, r3
	b @1
	@15:
	entry jt_8006CBE0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effStarPointEntry
	mr r23, r3
	b @1
	@16:
	entry jt_8006CC00
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effItemGetEntry
	mr r23, r3
	b @1
	@17:
	entry jt_8006CC1C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effStageClearEntry
	mr r23, r3
	b @1
	@18:
	entry jt_8006CC38
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effLevelupEntry
	mr r23, r3
	b @1
	@19:
	entry jt_8006CC58
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r22
	fmr f3, f27
	mr r5, r21
	fmr f4, f26
	fmr f5, f25
	fmr f6, f24
	bl effFallEntry
	mr r23, r3
	b @1
	@20:
	entry jt_8006CC88
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effMahojinEntry
	mr r23, r3
	b @1
	@21:
	entry jt_8006CCA4
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r27
	fmr f3, f27
	fmr f4, f26
	fmr f5, f25
	bl effNozleEntry
	mr r23, r3
	b @1
	@22:
	entry jt_8006CCCC
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effPuniBalloonEntry
	mr r23, r3
	b @1
	@23:
	entry jt_8006CCEC
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effKissEntry
	mr r23, r3
	b @1
	@24:
	entry jt_8006CD0C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	bl effSplashEntry
	mr r23, r3
	b @1
	@25:
	entry jt_8006CD2C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effNiceEntry
	mr r23, r3
	b @1
	@26:
	entry jt_8006CD48
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effMistEntry
	mr r23, r3
	b @1
	@27:
	entry jt_8006CD6C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r27
	fmr f3, f27
	fmr f4, f26
	fmr f5, f25
	bl effMist2Entry
	mr r23, r3
	b @1
	@28:
	entry jt_8006CD94
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effScanningEntry
	mr r23, r3
	b @1
	@29:
	entry jt_8006CDB0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r22
	fmr f3, f27
	mr r5, r21
	fmr f4, f26
	fmr f5, f25
	fmr f6, f24
	bl effParticleEntry
	mr r23, r3
	b @1
	@30:
	entry jt_8006CDE0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r27
	fmr f3, f27
	mr r5, r22
	fmr f4, f26
	fmr f5, f25
	bl effStardustEntry
	b @1
	@31:
	entry jt_8006CE08
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effTreasureMapEntry
	mr r23, r3
	b @1
	@32:
	entry jt_8006CE24
	xoris r3, r29, 0x8000
	lis r0, 0x4330
	stw r3, 0x14(r1)
	lis r4, double_to_int_802c47d8@ha
	lfd f4, double_to_int_802c47d8@l(r4)
	fmr f1, f29
	stw r0, 0x10(r1)
	fmr f2, f28
	fmr f3, f27
	mr r3, r30
	lfd f0, 0x10(r1)
	fsubs f4, f0, f4
	bl effSandarsEntry
	mr r23, r3
	b @1
	@33:
	entry jt_8006CE60
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effSheepEntry
	mr r23, r3
	b @1
	@34:
	entry jt_8006CE7C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effRankupEntry
	mr r23, r3
	b @1
	@35:
	entry jt_8006CE98
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effIrekaeruEntry
	mr r23, r3
	b @1
	@36:
	entry jt_8006CEB4
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r22
	fmr f3, f27
	fmr f4, f26
	fmr f5, f25
	fmr f6, f24
	bl effSmallStarEntry
	mr r23, r3
	b @1
	@37:
	entry jt_8006CEE0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effIbukiEntry
	mr r23, r3
	b @1
	@38:
	entry jt_8006CF00
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	mr r5, r27
	fmr f4, f26
	bl effMahornEntry
	mr r23, r3
	b @1
	@39:
	entry jt_8006CF28
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effToikiEntry
	mr r23, r3
	b @1
	@40:
	entry jt_8006CF48
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effUranokoEntry
	mr r23, r3
	b @1
	@41:
	entry jt_8006CF68
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effSyuryouEntry
	mr r23, r3
	b @1
	@42:
	entry jt_8006CF88
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r22
	fmr f3, f27
	mr r5, r20
	fmr f4, f26
	fmr f5, f25
	fmr f6, f24
	fmr f7, f23
	bl effHibashiraEntry
	mr r23, r3
	b @1
	@43:
	entry jt_8006CFBC
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effFireEntry
	mr r23, r3
	b @1
	@44:
	entry jt_8006CFE0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	fmr f4, f26
	fmr f5, f25
	fmr f6, f24
	bl effMachinegunEntry
	mr r23, r3
	b @1
	@45:
	entry jt_8006D008
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effRippleEntry
	mr r23, r3
	b @1
	@46:
	entry jt_8006D024
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effLasMonEntry
	mr r23, r3
	b @1
	@47:
	entry jt_8006D040
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effLaserEntry
	mr r23, r3
	b @1
	@48:
	entry jt_8006D05C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r29
	fmr f3, f27
	bl effIndirectEntry
	mr r23, r3
	b @1
	@49:
	entry jt_8006D07C
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effQueenEntry
	mr r23, r3
	b @1
	@50:
	entry jt_8006D0A0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effQueen2Entry
	mr r23, r3
	b @1
	@51:
	entry jt_8006D0BC
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	mr r4, r28
	fmr f3, f27
	fmr f4, f26
	bl effGonbabaBreathEntry
	mr r23, r3
	b @1
	@52:
	entry jt_8006D0E0
	fmr f1, f29
	mr r3, r30
	fmr f2, f28
	fmr f3, f27
	bl effMajinaiEntry
	mr r23, r3
	@1:
	entry jt_8006D0F8
	cmplwi r23, 0x0
	beq @53
	cmplwi r31, 0x0
	beq @53
	mr r3, r31
	la r4, lbl_8041A248(r2)
	bl strcmp
	cmpwi r3, 0x0
	beq @53
	mr r3, r23
	mr r4, r31
	bl effSetName
	@53:
	li r3, 0x2
	psq_l f31, 0xd8(r1), 0, 0
	lfd f31, 0xd0(r1)
	psq_l f30, 0xc8(r1), 0, 0
	lfd f30, 0xc0(r1)
	psq_l f29, 0xb8(r1), 0, 0
	lfd f29, 0xb0(r1)
	psq_l f28, 0xa8(r1), 0, 0
	lfd f28, 0xa0(r1)
	psq_l f27, 0x98(r1), 0, 0
	lfd f27, 0x90(r1)
	psq_l f26, 0x88(r1), 0, 0
	lfd f26, 0x80(r1)
	psq_l f25, 0x78(r1), 0, 0
	lfd f25, 0x70(r1)
	psq_l f24, 0x68(r1), 0, 0
	lfd f24, 0x60(r1)
	psq_l f23, 0x58(r1), 0, 0
	lfd f23, 0x50(r1)
	lmw r20, 0x20(r1)
	lwz r0, 0xe4(r1)
	mtlr r0
	addi r1, r1, 0xe0
	blr
}
// clang-format on
#endif
