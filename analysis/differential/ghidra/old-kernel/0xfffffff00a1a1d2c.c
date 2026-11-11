
/* WARNING: Removing unreachable block (ram,0xfffffff00a1a1e04) */
/* WARNING: Removing unreachable block (ram,0xfffffff00a1a1d9c) */

uint FUN_fffffff00a1a1d2c(long param_1,long param_2)

{
  uint uVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  ulong uVar6;
  uint uVar7;
  undefined8 uVar8;
  
  uVar7 = 1;
  if ((param_1 == 0) || (DAT_fffffff007baf028 == param_2)) goto LAB_fffffff00a1a1e7c;
  uVar8 = *(undefined8 *)(*(long *)(param_1 + 0x310) + 0x58);
  uVar3 = FUN_fffffff00a17db4c(param_2);
  if ((*(byte *)(param_2 + 2) & 1) == 0) {
                    /* WARNING: Does not return */
    pcVar2 = (code *)SoftwareBreakpoint(0xbffc,0xfffffff00a1a1ea0);
    (*pcVar2)();
  }
  uVar1 = uVar3 & 0xff;
  *(undefined1 *)(param_2 + 2) = 0;
  FUN_fffffff00a1bb65c(param_2 + 0x14);
  if (((uint)uVar8 >> 3 & 1) == 0) goto LAB_fffffff00a1a1dcc;
  uVar8 = *(undefined8 *)(param_1 + 0x310);
  uVar7 = 1;
  if ((uVar1 == 2) || (uVar1 == 8)) goto LAB_fffffff00a1a1e7c;
  FUN_fffffff00a22cb94(param_1);
  iVar4 = FUN_fffffff00a6fcdb8();
  if (iVar4 == 0) {
LAB_fffffff00a1a1dcc:
    if (8 < uVar1) {
      uVar7 = 0;
      goto LAB_fffffff00a1a1e7c;
    }
  }
  else {
    uVar5 = tpidr_el1;
    uVar5 = FUN_fffffff00a22d63c(uVar5);
    iVar4 = FUN_fffffff00a97d030(uVar5,"com.apple.private.set-exception-port");
    if (iVar4 != 0) goto LAB_fffffff00a1a1dcc;
    uVar6 = FUN_fffffff00a17c1bc(0xd,uVar8,0,0,param_2,0);
    uVar7 = 0;
    if (((uVar6 & 1) != 0) || (8 < uVar1)) goto LAB_fffffff00a1a1e7c;
  }
  uVar7 = 0x116 >> (ulong)(uVar3 & 0x1f);
LAB_fffffff00a1a1e7c:
  return uVar7 & 1;
}

