
undefined8 FUN_fffffff008421158(undefined8 param_1,long param_2)

{
  uint uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  char *pcVar5;
  ulong uVar6;
  long lVar7;
  long lVar8;
  uint uVar9;
  
  uVar2 = *(uint *)(param_2 + 4);
  if (uVar2 < 0x40) {
    bVar3 = *(byte *)(param_2 + 0x1a40);
    uVar1 = *(int *)(param_2 + 0xf78) + (uint)bVar3 + 1;
    if (uVar1 < 0x41) {
      if (uVar1 + *(byte *)(param_2 + 0x2a45) < 0x41) {
        uVar6 = 0;
        do {
          if (0x3f < *(byte *)(param_2 + 0x17fb + uVar6)) {
            iVar4 = FUN_fffffff0084ddb38(0x74,4);
            if (iVar4 == 0) {
              return 0xfffffc17;
            }
            iVar4 = FUN_fffffff0084ddb80(0x74);
            FUN_fffffff0085543f8();
            FUN_fffffff0084ddbb8(4);
            if (iVar4 == 0) {
              thunk_EXT_FUN_80110000038b6e98
                        (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                         "%lld %d AVE %s: %s:%d %s | HEVC VPS layer_id_in_nuh is out of range %d %d %d %d"
                        );
              return 0xfffffc17;
            }
            pcVar5 = 
            "%lld %d AVE %s: %s:%d %s | HEVC VPS layer_id_in_nuh is out of range %d %d %d %d\n";
            goto LAB_fffffff0084213a4;
          }
          uVar1 = (int)uVar6 + 1;
          uVar6 = (ulong)uVar1;
        } while (uVar1 <= uVar2);
        if (bVar3 != 0) {
          uVar6 = 0;
          uVar1 = uVar2;
          if (uVar2 < 2) {
            uVar1 = 1;
          }
          do {
            if (uVar2 != 0) {
              uVar9 = 0;
              lVar8 = 1;
              lVar7 = (ulong)(uVar1 + 1) - 1;
              do {
                uVar9 = uVar9 + *(byte *)(param_2 + 0x1a41 + uVar6 * 0x40 + lVar8);
                lVar8 = lVar8 + 1;
                lVar7 = lVar7 + -1;
              } while (lVar7 != 0);
              if (0x40 < uVar9) {
                iVar4 = FUN_fffffff0084ddb38(0x74,4);
                if (iVar4 == 0) {
                  return 0xfffffc17;
                }
                iVar4 = FUN_fffffff0084ddb80(0x74);
                FUN_fffffff0085543f8();
                FUN_fffffff0084ddbb8(4);
                if (iVar4 == 0) {
                  thunk_EXT_FUN_80110000038b6e98
                            (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                             "%lld %d AVE %s: %s:%d %s | HEVC VPS highest_layer_idx_plus1 sum is out of range %d %d %d %d"
                            );
                  return 0xfffffc17;
                }
                pcVar5 = 
                "%lld %d AVE %s: %s:%d %s | HEVC VPS highest_layer_idx_plus1 sum is out of range %d %d %d %d\n"
                ;
                goto LAB_fffffff0084213a4;
              }
            }
            uVar6 = uVar6 + 1;
          } while (uVar6 != bVar3);
        }
        return 0;
      }
      iVar4 = FUN_fffffff0084ddb38(0x74,4);
      if (iVar4 == 0) {
        return 0xfffffc17;
      }
      iVar4 = FUN_fffffff0084ddb80(0x74);
      FUN_fffffff0085543f8();
      FUN_fffffff0084ddbb8(4);
      if (iVar4 == 0) {
        thunk_EXT_FUN_80110000038b6e98
                  (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                   "%lld %d AVE %s: %s:%d %s | HEVC VPS output-layer-set total is out of range %d %d %d %d %d"
                  );
        return 0xfffffc17;
      }
      pcVar5 = 
      "%lld %d AVE %s: %s:%d %s | HEVC VPS output-layer-set total is out of range %d %d %d %d %d\n";
    }
    else {
      iVar4 = FUN_fffffff0084ddb38(0x74,4);
      if (iVar4 == 0) {
        return 0xfffffc17;
      }
      iVar4 = FUN_fffffff0084ddb80(0x74);
      FUN_fffffff0085543f8();
      FUN_fffffff0084ddbb8(4);
      if (iVar4 == 0) {
        thunk_EXT_FUN_80110000038b6e98
                  (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                   "%lld %d AVE %s: %s:%d %s | HEVC VPS layer-set total is out of range %d %d %d %d"
                  );
        return 0xfffffc17;
      }
      pcVar5 = "%lld %d AVE %s: %s:%d %s | HEVC VPS layer-set total is out of range %d %d %d %d\n";
    }
  }
  else {
    iVar4 = FUN_fffffff0084ddb38(0x74,4);
    if (iVar4 == 0) {
      return 0xfffffc17;
    }
    iVar4 = FUN_fffffff0084ddb80(0x74);
    FUN_fffffff0085543f8();
    FUN_fffffff0084ddbb8(4);
    if (iVar4 == 0) {
      thunk_EXT_FUN_80110000038b6e98
                (&MACH_HEADER,PTR_DAT_fffffff007cfb808,0,
                 "%lld %d AVE %s: %s:%d %s | HEVC VPS vps_max_layers_minus1 is out of range %d %d %d"
                );
      return 0xfffffc17;
    }
    pcVar5 = "%lld %d AVE %s: %s:%d %s | HEVC VPS vps_max_layers_minus1 is out of range %d %d %d\n";
  }
LAB_fffffff0084213a4:
  thunk_EXT_FUN_80110000031fc27c(pcVar5);
  return 0xfffffc17;
}

