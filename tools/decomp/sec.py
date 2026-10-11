import json,os,subprocess,sys
unit,sym=sys.argv[1],sys.argv[2]
subprocess.run([os.path.join('build','tools','objdiff-cli.exe'),'diff','-p','.','-u',unit,'-o',os.environ['TEMP']+'/fd.json',sym],capture_output=True)
d=json.load(open(os.environ['TEMP']+'/fd.json'))
print({s['name']:round(s.get('match_percent',0),2) for s in d['left']['sections'] if s['name'].startswith('.') and 'rela' not in s['name'] and s.get('match_percent') is not None})
