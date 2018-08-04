3DCoin Core version 0.13.3
========================

Release is now available from:

  <https://www.3dcoin.io/#download>

This is a new major version release, bringing new features and other improvements.

Please report bugs using the issue tracker at github:

  <https://github.com/blockchaintechllc/3dcoin/issues>

Upgrading
=========================

How to Upgrade
--------------

If you are running an older version, shut it down. Wait until it has completely
shut down (which might take a few minutes for older versions), then run the
installer (on Windows) or just copy over /Applications/3DCoin-Qt (on Mac) or
3dcoind/3dcoin-qt (on Linux).

Masternode update script
------------------------
```
curl -O https://raw.githubusercontent.com/BlockchainTechLLC/masternode/master/update.sh > update.sh
bash update.sh
```

Notable changes
===============

PrivateSend disabled
--------------------
BIP39 
-----

This BIP describes the implementation of a mnemonic code or mnemonic sentence -- a group of easy to remember words -- for the generation of deterministic wallets. 

https://github.com/bitcoin/bips/blob/master/bip-0039.mediawiki


RPC changes
-----------

There are few new RPC commands:
- `masternodelist pubkey` shows pubkey corresponding to masternodeprivkey for each masternode in the list;
- `dumphdinfo` displays some information about HD wallet (if available).

Command-line options
--------------------

New: `reindex-chainstate`

Experimental: `usehd`, `mnemonic`, `mnemonicpassphrase`, `hdseed`

See `Help -> Command-line options` in Qt wallet or `3dcoind --help` for more info.

Lots of backports, refactoring and bug fixes
--------------------------------------------

We backported some performance improvements from Bitcoin Core and aligned our codebase with their source a little bit better. We still do not have all the improvements so this work is going to be continued in next releases.

A lot of refactoring and other fixes should make code more reliable and easier to review now.

Experimental HD wallet
----------------------

This release includes experimental implementation of BIP39/BIP44 compatible HD wallet. Wallet type (HD or non-HD) is selected when wallet is created via `usehd` command-line option, default is `1` which means that the HD wallet is going to be used. If you decide to use mnemonic passphrase, you can specify BIP39 (see `mnemonic` and `mnemonicpassphrase` command-line options) but you can do so only on initial wallet creation and can't change these afterwards. If you don't specify them, mnemonic is going to be generated randomly and mnemonic passphrase is going to be just a blank string.

**WARNING:** The way it's currently implemented is NOT safe and is NOT recommended to use on mainnet. Wallet is created unencrypted with mnemonic stored inside, so even if you encrypt it later there will be a short period of time when mnemonic is stored in plain text. This issue will be addressed in future releases.

