// proto: static void shuryolightSetAnim(s32 index, s32 anim);
static void shuryolightSetAnim(s32 index, s32 anim) {
    ShuryoLight* light = &slhp->lights[index];

    light->status = anim;
    animPoseSetAnim(light->npc->poseId, light->anims[anim], TRUE);
}
