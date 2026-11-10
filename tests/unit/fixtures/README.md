# Test fixtures

`BuildManifest.minimal.plist` is a synthetic, hand-written plist for parser tests. It is not extracted from any Apple image. Its 48-byte digest is `bytes(range(48))`, not a real payload hash.

Do not add extracted firmware, device data, or production manifest excerpts here. Keep fixtures small and synthetic.
