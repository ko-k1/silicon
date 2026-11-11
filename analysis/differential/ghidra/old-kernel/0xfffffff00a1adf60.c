
/* WARNING: Removing unreachable block (ram,0xfffffff00a1ae0e8) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a1ae06c) */

undefined8
FUN_fffffff00a1adf60
          (long param_1,uint param_2,long param_3,undefined8 param_4,uint param_5,int param_6)

{
  uint uVar1;
  int iVar2;
  long lVar3;
  undefined8 uVar4;
  uint uVar5;
  ulong uVar6;
  uint uVar7;
  
  if ((param_2 & 0xffffc001) != 0) {
    return 4;
  }
  uVar5 = (uint)param_4;
  if (1 < param_3 + 1U) {
    if (4 < (uVar5 & 0x1fffffff) - 1) {
      return 4;
    }
    iVar2 = FUN_fffffff00a1a1ea0(param_1,param_3);
    if (iVar2 == 0) {
      return 0x11;
    }
  }
  if (0x1b < param_5) {
    return 4;
  }
  if ((1 << (ulong)(param_5 & 0x1f) & 0xa03c6ffU) == 0) {
    return 4;
  }
  uVar7 = uVar5 >> 0x1d & 1;
  if ((uVar5 & 0x1fffffff) == 4) {
    uVar7 = 1;
  }
  if ((-1 < (int)uVar5) && (uVar7 != 0)) {
    return 4;
  }
  uVar4 = tpidr_el1;
  lVar3 = FUN_fffffff00a22d63c(uVar4);
  if (((lVar3 != 0) && (lVar3 = FUN_fffffff00a22cb94(), lVar3 != 0)) &&
     (uVar4 = (*pcRam00000000000001c8)(lVar3,"com.apple.private.set-exception-port"),
     (int)uVar4 == 0)) {
    return uVar4;
  }
  if (param_1 == 0) {
    uVar6 = 0;
LAB_fffffff00a1ae14c:
    if ((param_3 + 1U < 2) || (DAT_fffffff007baf028 == param_3)) goto LAB_fffffff00a1ae158;
    if (param_1 == 0) {
LAB_fffffff00a1ae1d4:
      if ((5 < (uVar5 & 0x1fffffff)) || ((1 << (ulong)(uVar5 & 0x1f) & 0x34U) == 0))
      goto LAB_fffffff00a1ae1f0;
    }
    else if (((uint)uVar6 >> 1 & 1) == 0) {
      if (((uint)uVar6 >> 9 & 1) != 0) goto LAB_fffffff00a1ae1d4;
    }
    else if ((uVar6 & 0x604) != 0) goto LAB_fffffff00a1ae1d4;
LAB_fffffff00a1ae158:
    uVar4 = 0;
  }
  else {
    uVar6 = *(ulong *)(*(long *)(param_1 + 0x310) + 0x58);
    if (((param_1 == 0) || (lVar3 = FUN_fffffff00a22cb94(param_1), lVar3 == 0)) ||
       (iVar2 = (*pcRam00000000000001c8)(lVar3,"com.apple.security.only-one-exception-port"),
       iVar2 != 0)) {
LAB_fffffff00a1ae0b4:
      uVar6 = *(ulong *)(*(long *)(param_1 + 0x310) + 0x58);
      goto LAB_fffffff00a1ae14c;
    }
    uVar7 = 1;
    if ((uVar6 & 4) == 0) {
      uVar7 = (uint)((uVar6 & 0x600) != 0);
    }
    uVar1 = (uint)uVar6 >> 9 & 1;
    if ((uVar6 & 2) != 0) {
      uVar1 = uVar7;
    }
    if ((uVar1 == 0) || (param_6 != 0)) goto LAB_fffffff00a1ae0b4;
LAB_fffffff00a1ae1f0:
    FUN_fffffff00a9eb5a0(param_4,param_2,6);
    uVar4 = 0x35;
  }
  return uVar4;
}

