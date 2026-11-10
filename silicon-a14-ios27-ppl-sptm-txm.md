# CASE-0001 — A14 / iOS 27.0.1: PPL, SPTM, and TXM status

- **Status:** Investigating
- **Assessment date:** 2026-11-05
- **Target:** iPhone 12 mini / A14 / `iPhone13,1` / iOS `27.0.1`
- **Candidate build:** `24A446` (device installation still needs local confirmation)
- **Related manifest:** [`targets/manifests/iphone12mini-ios27.0.1.yaml`](../../../targets/manifests/iphone12mini-ios27.0.1.yaml)

## Executive assessment

The strongest available **SoC-level baseline** classifies A14 as a PPL-generation platform and lists SPTM support for A15-or-later and M2-or-later SoCs. That is meaningful evidence against native SPTM support on A14. However, the Apple documentation currently located is dated 2026-01-28, before iOS 27, and does not explicitly certify the runtime configuration of A14 on iOS 27.0.1.

Post-iOS-27 community sources conflict:

- The Apple Wiki says SPTM-bypass requirements extend to A13/A14 and M1 from iOS 27.0 beta.
- A current iOS 27 jailbreak tracker says A14+ needs an SPTM bypass in its summary, but its detailed device matrix places A14/M1 in a **PPL** group and labels the A14 PPL-bypass question unresolved.
- ModStaller groups `TXM/SPTM` in one device-table column and labels A14 as having that state “from iOS 27”; its footnote describes iOS 27 treating devices as TXM devices. Its A14 row is expected/untested, and the project does not demonstrate SPTM activation on an A14 device.
- An iOS 27.0.1 SPTM analysis exists for iPhone Air (`iPhone18,4`, T8150). It proves that the same OS build has an SPTM image for that target, not that an A14 restore image contains or activates it.

**Working conclusion:** Keep A14's SoC baseline as **PPL-oriented**. Track iOS 27 TXM-related behavior separately. Set A14 SPTM runtime status to **unknown / disputed**, not confirmed and not conclusively absent, until evidence is extracted from the exact `iPhone13,1` Build 24A446 firmware and corroborated with target-specific boot/runtime observations.

This case does not assume that a Kernel Read/Write primitive implies bypass of PPL, SPTM, or TXM policy. It records architecture and evidence state only.

## 1. Scope and identity

| Field | Value | Status |
|---|---|---|
| Device | iPhone 12 mini | Target selected for this case |
| Product type | `iPhone13,1` | Verify on device |
| SoC | A14 | User-specified target; verify locally |
| OS | iOS `27.0.1` | User-specified target |
| Build | `24A446` | IPSW catalog associates this build with `iPhone13,1`; verify installed build locally |

The IPSW.dev build index lists iPhone 12 mini (`iPhone13,1`) among the devices for iOS 27.0.1 / Build 24A446 [EVD-0007]. This is a third-party catalog and is not a substitute for reading the device's own build identity.

## 2. Terminology that must remain separate

| Term | Meaning in this case | What it does **not** prove |
|---|---|---|
| **PPL** | Page Protection Layer; Apple documents it as the page/code-integrity protection model used on supported older platforms. | A PPL-related source does not establish that every PPL property is unchanged on a later OS build. |
| **SPTM** | Secure Page Table Monitor; Apple describes a higher-privileged monitor relying on newer silicon primitives and replacing PPL on supported platforms. | An SPTM image for another SoC, or an SPTM-related bypass label, does not prove A14 activation. |
| **TXM** | Trusted Execution Monitor; Apple's architecture description treats it as a distinct, lower-privileged policy-enforcement component working with SPTM on SPTM platforms. | TXM presence or TXM-related JIT behavior is not, by itself, proof that SPTM is present or active. |
| **Firmware presence** | A component or image appears in a restore image or filesystem. | Presence alone does not prove that the component applies to, is selected for, is loaded on, or is active on a particular device. |
| **Runtime activation** | Target-specific evidence shows the component is selected and running in the actual booted environment. | A build-level artifact listing alone does not establish runtime activation. |

Do not use `TXM`, `SPTM`, and `TXM/SPTM` as interchangeable labels in silicon records.

## 3. Evidence review

### 3.1 Apple platform-security documentation — strong SoC baseline, limited OS-version scope

Apple's SoC security page states that SPTM is supported on A15-or-later and M2-or-later SoCs and replaces PPL on supported platforms [EVD-0001]. Apple's operating-system-integrity page explains that SPTM and TXM work together, and that SPTM relies on silicon primitives available only on the listed processors [EVD-0001].

This strongly supports the baseline classification **A14 → PPL generation; SPTM → A15+/M2+ generation**. But the official page's publication date is 2026-01-28, before iOS 27.0 beta and iOS 27.0.1. It is not an explicit statement about the A14 runtime configuration of Build 24A446. Treat it as authoritative SoC-level documentation, not as final target-specific proof.

### 3.2 The Apple Wiki — explicit contrary claim, no target evidence attached

The Apple Wiki's PPL/SPTM bypass page says that from iOS 27.0 beta, SPTM bypasses are required on A13-A14 and M1 as well [EVD-0002]. The page was last modified on 2026-09-23.

The page is useful as a signal that the jailbreak community observed a changed requirement. However, the statement does not cite A14-specific firmware evidence, boot evidence, or a technical explanation distinguishing SPTM from TXM or changed PPL policy. Its use of the term “SPTM bypass” must therefore remain a **secondary-source claim**, not a confirmed architecture fact.

### 3.3 Dopamine 3.0 release notes — clear mechanism scope, but not a direct A14/iOS 27 ruling

The maintainer's 3.0 release notes separately describe:

- Titan as a PPL/SPTM bypass for devices on iOS 16.5.1–17.3.1.
- momentarius as a PPL bypass for A12/A13 on specified iOS 16/18/26 ranges.
- generic SPTM-device support up to iOS 27.0 betas in Corellium, while real-device support is limited to iOS 17.3.1 because of the lack of an SPTM bypass on later versions [EVD-0003].

This source confirms that the project distinguishes PPL and SPTM mechanisms, and that Corellium support is not equivalent to real-device support. It does **not** say that A14 has SPTM on iOS 27.0.1, nor does it establish an A14 PPL-bypass implementation.

### 3.4 ModStaller — TXM-related iOS 27 behavior, not proof of SPTM

ModStaller's supported-device table groups the column as `TXM/SPTM` and labels the A14 iPhone 12 series “from iOS 27”. The same README says that its A13/A14 test coverage is still expected/untested and describes iOS 27 as treating supported devices like TXM devices [EVD-0004].

This is relevant evidence that iOS 27 may introduce TXM-related behavior or handling on A13/A14. But the combined column heading is ambiguous, and its A14 row is not a confirmed device test. The source cannot establish that SPTM itself is active on A14. Its own wording points to **TXM behavior** as a separate line of inquiry.

### 3.5 iOS 27 jailbreak tracker — an internal classification conflict

The tracker updated through 2026-11-04 says in its summary that A14+ still needs an SPTM bypass. In the detailed device matrix, however, it separates:

- A14/M1 as the **PPL group**, with the PPL-bypass question unresolved.
- A15–A18/M2–M4 as the **SPTM group** [EVD-0005].

The tracker also asks whether the upcoming kernel write-up contains A14/PPL material. This is a material internal inconsistency. The detailed matrix is more precise about chip grouping, but neither presentation is primary evidence. Do not resolve the conflict by selecting whichever sentence is more convenient.

### 3.6 Same-build SPTM research on iPhone Air — comparison only

A public reverse-engineering report identifies an SPTM image (`sptm.t8150.release.im4p`) in the iOS 27.0.1 Build 24A446 restore image for iPhone Air (`iPhone18,4`, T8150) [EVD-0006].

This proves that Build 24A446 includes an SPTM component for that target. It does not prove that the `iPhone13,1` restore image contains the same component, and it certainly does not prove A14 runtime activation. Build equality is not hardware-target equality.

## 4. Competing hypotheses

| ID | Hypothesis | Current assessment | Evidence that would move it |
|---|---|---|---|
| H1 | A14 retains PPL as its page-protection architecture on iOS 27.0.1; TXM-related handling may also exist. | **Most consistent with SoC documentation and the detailed device matrix; not target-confirmed.** | Exact A14 IPSW manifest/component inventory plus boot/runtime evidence. |
| H2 | iOS 27 enables SPTM on A14 despite the documented SoC-generation boundary. | **Low support / disputed.** Community sources state an SPTM-bypass requirement, but no A14-specific technical proof has been identified. | A14-specific SPTM image, device applicability metadata, boot selection, and runtime confirmation. |
| H3 | The reported “SPTM bypass” requirement is shorthand for a TXM change, a changed PPL condition, or another iOS 27 policy transition. | **Plausible, unconfirmed.** TXM-related behavior is independently reported for A13/A14. | Technical explanation from the original researcher or target-bound artifacts clarifying the protected boundary. |

H1 is the working model, not a final finding. H2 must remain open until the exact A14 firmware is checked.

## 5. Questions to resolve

1. Does the exact iPhone 12 mini Build 24A446 restore image contain an SPTM image, and if so, is it marked as applicable to `iPhone13,1`?
2. Does that restore image contain `Ap,TrustedExecutionMonitor` or another TXM component, and what are its applicability/selection conditions?
3. Does iOS 27.0.1 load TXM on A14 independently of SPTM, or is the reported behavior a tooling/policy-level classification?
4. Does the A14 kernel/boot configuration still initialize PPL, and what target-specific evidence establishes that it is active?
5. Are the post-iOS-27 “SPTM bypass” statements based on observed SPTM execution, a TXM artifact, a PPL policy change, or merely jailbreak compatibility behavior?
6. Are claims about `iPhone13,1` being representative of all A14 variants supported, or do product/build differences require separate profiles?

## 6. Safe verification plan

The next phase is **read-only artifact verification**, not exploit development.

1. **Lock target identity.** Record on-device ProductType, SoC identifier if exposed, OS version, and Build. Do not infer installed Build solely from the iOS marketing version.
2. **Acquire the exact restore artifact.** Use the iPhone 12 mini / `iPhone13,1` / Build 24A446 image. Preserve source URL, acquisition time, byte length, and SHA-256.
3. **Inventory the restore manifest.** Record component names, board/product applicability, and references for PPL/SPTM/TXM-related images. Presence and applicability must be separate fields.
4. **Inventory filesystem and boot metadata.** Record whether relevant images and configuration references exist for this product type. Do not interpret a filename alone as proof of loading.
5. **Use the iPhone Air image only as a control.** Compare the same Build number across `iPhone18,4` and `iPhone13,1` without transferring conclusions across SoCs.
6. **Correlate non-invasive runtime observations.** Where available, record read-only diagnostics and boot/runtime metadata that identify the selected components. No patching, bypass execution, or device-state modification is part of this case.
7. **Review counter-evidence.** Ask a second reviewer to assess whether the collected evidence proves presence, applicability, loading, or active enforcement—four different claims.

### Evidence thresholds

| Claim | Minimum evidence standard |
|---|---|
| Component is present in an IPSW | Exact target IPSW inventory + cryptographic hash |
| Component applies to A14/iPhone13,1 | Manifest/board applicability tied to exact product type |
| Component is selected for boot | Target-specific boot/restore configuration evidence |
| Component is loaded | Target-specific non-invasive runtime evidence or equivalent authoritative boot evidence |
| Component is actively enforcing a protection boundary | Runtime/architecture evidence that links the active component to the relevant enforcement path |

A missing standalone image is not, by itself, sufficient to prove that no equivalent functionality exists. A present image is not sufficient to prove that it is loaded. TXM presence does not prove SPTM presence.

## 7. Provisional target-manifest state

The target manifest should preserve uncertainty:

```yaml
protection:
  PPL:
    state: inferred
    evidence: [EVD-0001, EVD-0005]
    note: "A14 SoC baseline; exact Build 24A446 runtime confirmation pending"
  SPTM:
    state: unknown
    assessment: disputed
    evidence: [EVD-0001, EVD-0002, EVD-0005, EVD-0006]
    note: "A14-specific presence, applicability, and runtime activation unverified"
  TXM:
    state: unknown
    assessment: "iOS 27 A13/A14 handling reported; target runtime status unverified"
    evidence: [EVD-0004]
```

Do not mark SPTM as `confirmed`, `not-applicable`, or `absent` until target-specific evidence meets the thresholds above.

## 8. Decision log

- **2026-11-05:** Opened CASE-0001 because public sources conflict on whether A13/A14 require an SPTM bypass from iOS 27.
- **2026-11-05:** Adopted A14→PPL as the working SoC baseline, not as an iOS 27.0.1 runtime conclusion.
- **2026-11-05:** Split TXM into an independent research component to avoid interpreting TXM-related iOS 27 behavior as proof of SPTM.
- **2026-11-05:** Kept SPTM runtime state `unknown` and case status `investigating` pending exact-target firmware evidence.

## 9. Sources

All sources below were accessed on 2026-11-05. Evidence IDs map to machine-readable records under `evidence/`.

| ID | Source | Class | Scope / limitation |
|---|---|---|---|
| EVD-0001 | [Apple Platform Security — Apple SoC Security](https://support.apple.com/ja-jp/guide/security/sec87716a080/web) and [Operating System Integrity](https://support.apple.com/ja-jp/guide/security/sec8b776536b/web) | Primary | A15+/M2+ SPTM baseline; page published 2026-01-28, predates iOS 27. |
| EVD-0002 | [The Apple Wiki — PPL/SPTM Bypasses](https://theapplewiki.com/wiki/PPL/SPTM_Bypasses) | Secondary | Explicit A13/A14/M1 SPTM-bypass claim from iOS 27 beta; no A14 artifact evidence cited. |
| EVD-0003 | [opa334/Dopamine — 3.0 release](https://github.com/opa334/Dopamine/releases/tag/3.0) | Primary project release | Distinguishes Titan PPL/SPTM and momentarius PPL; does not resolve A14/iOS 27.0.1. |
| EVD-0004 | [Crafttino21/ModStaller](https://github.com/Crafttino21/ModStaller) | Secondary implementation note | A14 listed as TXM/SPTM “from iOS 27”; A14 row is untested; combined label is ambiguous. |
| EVD-0005 | [iMaxTomas/ios27-jb-tracker](https://github.com/iMaxTomas/ios27-jb-tracker) | Secondary tracker | Summary says A14+ needs SPTM bypass; detailed matrix classifies A14/M1 as PPL. Snapshot dated 2026-11-04. |
| EVD-0006 | [IvanIVGrozny/iOS27.0.1-SPTM-Research](https://github.com/IvanIVGrozny/iOS27.0.1-SPTM-Research) | Secondary technical analysis | SPTM image for iPhone Air (`iPhone18,4`, T8150); not A14 evidence. |
| EVD-0007 | [IPSW.dev — Build 24A446](https://www.ipsw.dev/build/24A446) | Secondary firmware catalog | Lists iPhone 12 mini (`iPhone13,1`) for this build; installed device identity remains to be verified. |
| EVD-0008 | [star-studios-official/azahar — JIT implementation notes](https://github.com/star-studios-official/azahar/blob/master/JIT_IMPLEMENTATION.md) | Secondary implementation note | Describes A13/A14/M1 TXM firmware-path handling on iOS 27; not proof of SPTM activation. |

---

**Current verdict: unresolved at the target-runtime level.** A14 should remain PPL-oriented in the architecture model, with TXM-related iOS 27 behavior tracked separately and SPTM kept as a disputed, unverified claim until the exact A14 Build 24A446 artifacts are examined.
