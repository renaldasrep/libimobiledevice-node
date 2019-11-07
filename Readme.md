## Node native add-on for libimobiledevice

The main focus of the library is with electron apps. More info in their official site [libimobiledevice.org](http://libimobiledevice.org)

## Installation

### Mac

```bash
$ yarn add libimobiledevice
```

### Windows

#### Requeriments

For using libimobiledevice-node on windows the following requeriments are needed:

- Install **Visual Studio 2017 community**.
- Install **Windows SDK 8.1**.
- Be sure **Powershell** command can be called from the command line.
- Add **msbuild.exe** on windows **PATH**.

```bash
$ yarn add libimobiledevice
```

## Todo

Binaries ported

- [x] idevice_id
- [ ] idevicebackup
- [ ] idevicebackup2
- [ ] idevicecrashreport
- [ ] idevicedate
- [ ] idevicedebug
- [ ] idevicedebugserverproxy
- [ ] idevicediagnostics
- [ ] ideviceenterrecovery
- [ ] ideviceimagemounter
- [x] ideviceinfo
- [ ] idevicename
- [ ] idevicenotificationproxy
- [x] idevicepair
- [ ] ideviceprovision
- [ ] idevicescreenshot
- [ ] idevicesyslog

## Usage

```javascript
const lib = require('libimobiledevice')

// List of devices
lib.id(data => console.log(data))

// Device info
lib.info({
	debug: true,
    simple: true,
    udid: 'string',
    domain: 'string',
	key: 'string'
}, (err, data) => console.log(err, data))
```

