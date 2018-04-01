Sample init scripts and service configuration for 3dcoind
==========================================================

Sample scripts and configuration files for systemd, Upstart and OpenRC
can be found in the contrib/init folder.

    contrib/init/3dcoind.service:    systemd service unit configuration
    contrib/init/3dcoind.openrc:     OpenRC compatible SysV style init script
    contrib/init/3dcoind.openrcconf: OpenRC conf.d file
    contrib/init/3dcoind.conf:       Upstart service configuration file
    contrib/init/3dcoind.init:       CentOS compatible SysV style init script

1. Service User
---------------------------------

All three Linux startup configurations assume the existence of a "3dcoin" user
and group.  They must be created before attempting to use these scripts.
The OS X configuration assumes 3dcoind will be set up for the current user.

2. Configuration
---------------------------------

At a bare minimum, 3dcoind requires that the rpcpassword setting be set
when running as a daemon.  If the configuration file does not exist or this
setting is not set, 3dcoind will shutdown promptly after startup.

This password does not have to be remembered or typed as it is mostly used
as a fixed token that 3dcoind and client programs read from the configuration
file, however it is recommended that a strong and secure password be used
as this password is security critical to securing the wallet should the
wallet be enabled.

If 3dcoind is run with the "-server" flag (set by default), and no rpcpassword is set,
it will use a special cookie file for authentication. The cookie is generated with random
content when the daemon starts, and deleted when it exits. Read access to this file
controls who can access it through RPC.

By default the cookie is stored in the data directory, but it's location can be overridden
with the option '-rpccookiefile'.

This allows for running 3dcoind without having to do any manual configuration.

`conf`, `pid`, and `wallet` accept relative paths which are interpreted as
relative to the data directory. `wallet` *only* supports relative paths.

For an example configuration file that describes the configuration settings,
see `contrib/debian/examples/3dcoin.conf`.

3. Paths
---------------------------------

3a) Linux

All three configurations assume several paths that might need to be adjusted.

Binary:              `/usr/bin/3dcoind`  
Configuration file:  `/etc/3dcoin/3dcoin.conf`  
Data directory:      `/var/lib/3dcoind`  
PID file:            `/var/run/3dcoind/3dcoind.pid` (OpenRC and Upstart) or `/var/lib/3dcoind/3dcoind.pid` (systemd)  
Lock file:           `/var/lock/subsys/3dcoind` (CentOS)  

The configuration file, PID directory (if applicable) and data directory
should all be owned by the 3dcoin user and group.  It is advised for security
reasons to make the configuration file and data directory only readable by the
3dcoin user and group.  Access to 3dcoin-cli and other 3dcoind rpc clients
can then be controlled by group membership.

3b) Mac OS X

Binary:              `/usr/local/bin/3dcoind`  
Configuration file:  `~/Library/Application Support/3DCoin/3dcoin.conf`  
Data directory:      `~/Library/Application Support/3DCoin`
Lock file:           `~/Library/Application Support/3DCoin/.lock`

4. Installing Service Configuration
-----------------------------------

4a) systemd

Installing this .service file consists of just copying it to
/usr/lib/systemd/system directory, followed by the command
`systemctl daemon-reload` in order to update running systemd configuration.

To test, run `systemctl start 3dcoind` and to enable for system startup run
`systemctl enable 3dcoind`

4b) OpenRC

Rename 3dcoind.openrc to 3dcoind and drop it in /etc/init.d.  Double
check ownership and permissions and make it executable.  Test it with
`/etc/init.d/3dcoind start` and configure it to run on startup with
`rc-update add 3dcoind`

4c) Upstart (for Debian/Ubuntu based distributions)

Drop 3dcoind.conf in /etc/init.  Test by running `service 3dcoind start`
it will automatically start on reboot.

NOTE: This script is incompatible with CentOS 5 and Amazon Linux 2014 as they
use old versions of Upstart and do not supply the start-stop-daemon utility.

4d) CentOS

Copy 3dcoind.init to /etc/init.d/3dcoind. Test by running `service 3dcoind start`.

Using this script, you can adjust the path and flags to the 3dcoind program by
setting the 3DCOIND and FLAGS environment variables in the file
/etc/sysconfig/3dcoind. You can also use the DAEMONOPTS environment variable here.

4e) Mac OS X

Copy org.3dcoin.3dcoind.plist into ~/Library/LaunchAgents. Load the launch agent by
running `launchctl load ~/Library/LaunchAgents/org.3dcoin.3dcoind.plist`.

This Launch Agent will cause 3dcoind to start whenever the user logs in.

NOTE: This approach is intended for those wanting to run 3dcoind as the current user.
You will need to modify org.3dcoin.3dcoind.plist if you intend to use it as a
Launch Daemon with a dedicated 3dcoin user.

5. Auto-respawn
-----------------------------------

Auto respawning is currently only configured for Upstart and systemd.
Reasonable defaults have been chosen but YMMV.
