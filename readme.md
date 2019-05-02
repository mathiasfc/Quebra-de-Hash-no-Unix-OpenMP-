gcc -o myexec.exe -fopenmp -lcrypt file.c

./myexec.exe

 pp12711
 .......




===================================================================
SPARTA:
ssh portoalegre\\13104495@sparta.pucrs.br

MARFIM:
ssh -o PasswordAuthentication=yes pp12711@marfim.lad.pucrs.br

====================================================================
GET:

MARFIM > SPARTA (Roda SPARTA)
scp -r  pp12711@marfim.lad.pucrs.br:/home/pp12711/openmp/decrypt /home/PORTOALEGRE/13104495/DriveH/PP/<nome pasta>

SPARTA > LOCAL (Roda LOCAL)
scp -r  portoalegre\\13104495@sparta.pucrs.br:/home/PORTOALEGRE/13104495/DriveH/PP/results /home/mathias/Desktop/

====================================================================
SET:

LOCAL > SPARTA (Em Local)
scp -r  /home/mathias/Documents/github/Quebra-de-Hash-no-Unix-OpenMP-/ portoalegre\\13104495@sparta.pucrs.br:/home/PORTOALEGRE/13104495/DriveH/PP/

SPARTA > MARFIM (Em SPARTA)
scp -r  /home/PORTOALEGRE/13104495/DriveH/PP/Quebra-de-Hash-no-Unix-OpenMP-/ pp12711@marfim.lad.pucrs.br:/home/pp12711/decrypt/

====================================================================

Sequencial(s):

129.78 / 138.23 / 180.44 / 143.12 / 114.67 / 110.57

Paralelo Cluster(s):

1 - 106.86 / 173.88 / 128.81 / 121.46 / 112.29 

2 - 132.43 / 153.55 / 112.47 / 113.96 / 117.35 = 125.952

4 - 106.21 / 96.97 / 104.25 / 84.08 / 86.18 = 95.538

8 - 42.64 / 62.19 / 39.79 / 30.72 / 65.71 / 52.23 = 48.88

16 - 15.10 / 14.54 / 18.33 / 14.79 / 17.13 / 18.96  = 16.475







