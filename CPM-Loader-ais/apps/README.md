Starting Tasks Manually
-----------------------

```bash
shell 1
<root>/<ssp>/eta-ais$. changeCatEnvToHere.sh
<root>/<ssp>/eta-ais$./bin/scs

shell 2..N
<root>/<ssp>/eta-ais$. changeCatEnvToHere.sh

... and one of ...

<root>/<ssp>/eta-ais$./bin/aisJhm2DataServer --instance AisJhm2DataServer
<root>/<ssp>/eta-ais$./bin/LpsSaJobMgrApp --instance LpsSaJobMgrApp
<root>/<ssp>/eta-ais$./bin/LpsSaTotalsApp --instance LpsSaTotalsApp
<root>/<ssp>/eta-ais$./bin/LpsSaListMgrApp --instance LpsSaListMgrApp
```

Starting lighttpd on local host
-------------------------------
Make sure lighttpd is installed on local host.  If not...
```bash
sudo apt-get install lighttpd
```
Make sure the web app is copied to the correct place.  This is not part of the local host build.
```bash
<root>/<ssp>/CPM-Loader-ais/apps$. copy_WebUI_to_www.sh
```

Launch lighttpd (without detaching into background mode).
This launches lighttpd on port 8080.
```bash
<root>/<ssp>$lighttpd -f CPM-Loader-ais/apps/lighttpd.conf -D
```

Browse to the app: http://localhost:8080/CPM
