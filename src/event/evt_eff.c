#include "mario/mario.h"
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

USER_FUNC(evt_eff) {
	s32* args = event->args;
	s32* p;
	s32* q;
	s32* r;
	const char* effName;
	const char* effSet;
	s32 int2, int3, int4, int5, int6, int7, int8, int9;
	s32 int10, int11, int12, int13, int14;
	EffectEntry* entry;
	f32 float2, float3, float4, float5, float6, float7, float8,
		float9, float10, float11, float12, float13, float14;

	p = args;
	q = args;
	r = args;
	effName = (const char*)evtGetValue(event, *(p++));
	evtGetValue(event, *(q++));
	evtGetValue(event, *(r++));
	effSet = (const char*)evtGetValue(event, *(p++));
	evtGetValue(event, *(q++));
	evtGetValue(event, *(r++));
	int2 = evtGetValue(event, p[0]);
	int3 = evtGetValue(event, p[1]);
	int4 = evtGetValue(event, p[2]);
	int5 = evtGetValue(event, p[3]);
	int6 = evtGetValue(event, p[4]);
	int7 = evtGetValue(event, p[5]);
	int8 = evtGetValue(event, p[6]);
	int9 = evtGetValue(event, p[7]);
	int10 = evtGetValue(event, p[8]);
	int11 = evtGetValue(event, p[9]);
	int12 = evtGetValue(event, p[10]);
	int13 = evtGetValue(event, p[11]);
	int14 = evtGetValue(event, p[12]);
	float2 = evtGetFloat(event, q[0]);
	float3 = evtGetFloat(event, q[1]);
	float4 = evtGetFloat(event, q[2]);
	float5 = evtGetFloat(event, q[3]);
	float6 = evtGetFloat(event, q[4]);
	float7 = evtGetFloat(event, q[5]);
	float8 = evtGetFloat(event, q[6]);
	float9 = evtGetFloat(event, q[7]);
	float10 = evtGetFloat(event, q[8]);
	float11 = evtGetFloat(event, q[9]);
	float12 = evtGetFloat(event, q[10]);
	float13 = evtGetFloat(event, q[11]);
	float14 = evtGetFloat(event, q[12]);

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

#pragma push
#pragma optimization_level 2
s32 evt_eff64(EventEntry *event, BOOL isFirstCall)
{
  s32 *args;
  s32 *pi;
  s32 *pr;
  s32 *pf;
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
  pi = args;
  pr = args;
  pf = args;
  effName = (const char *) evtGetValue(event, *(pi++));
  evtGetValue(event, *(pr++));
  evtGetValue(event, *(pf++));
  effSet = (const char *) evtGetValue(event, *(pi++));
  u1a = evtGetValue(event, *(pr++));
  u1b = evtGetValue(event, *(pf++));
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
      effect = effCrystalN64Entry(int2, int7, float3, float4, float5, float6);
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
    if (strcmp(effName, ""))
    {
      effSetName(effect, effName);
    }
  }
  return 2;
}

#pragma pop

USER_FUNC(evt_eff_softdelete) {
	effSoftDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_delete) {
	effDelete(effNameToPtr((const char*)evtGetValue(event, *event->args)));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_softdelete_ptr) {
	effSoftDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

USER_FUNC(evt_eff_delete_ptr) {
	effDelete((EffectEntry*)evtGetValue(event, *event->args));
	return EVT_RETURN_DONE;
}

extern s32 marioGetPartyId(void);
extern s32 marioGetExtraPartyId(void);
extern void* partyGetPtr(s32 id);
extern EffectEntry* effFukidashiEntry(s32 a, s32 b, s32 c, s32 d, f32 x, f32 y, f32 z, f32 w, f32 e);

#pragma push
#pragma opt_propagation off
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
			h = *(f32*)((u8*)marioGetPtr() + MWOFF(0x1b8));
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
#ifdef VERSION_G8ME01
				// US: the Flurrie bubble sits at a fixed height
				{ f32 yy = 2.0f * *(f32*)((u8*)p + 0xf0) / 3.0f; f32 ww; if (*(s8*)((u8*)p + 0x31) == 5) yy = 30.0f; ww = *(f32*)((u8*)p + 0xf0) / 3.0f; entry = effFukidashiEntry(a, b, -2, d, 0.0f, yy, 0.0f, ww, e); }
#else
				h = *(f32*)((u8*)p + 0xf0);
				{ f32 yy = 2.0f * h / 3.0f; f32 ww = h / 3.0f; entry = effFukidashiEntry(a, b, -2, d, 0.0f, yy, 0.0f, ww, e); }
#endif
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
#pragma pop
