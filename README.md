# chmod-parser

Lav en funktion der kan tage et sæt filrettigheder og en chmod-kommando, og
producere et nyt sæt filrettigheder, der afspejler chmod-kommandoen. Den
behøver ikke faktisk at ændre filens rettigheder, da det kun er en øvelse i at
parse strings.

- Man kan læse, skrive og eksekvere filer ved at tilføje en kombination af
  `+r`, `+w` og `+x`
- Man kan fjerne de samme rettigheder med et minus i stedet, `-r`, `-w` og `-x`
- Man kan kombinere en til flere rettigheder, fx `+rw`, `+rwx`, `-wx`
- Man kan angive om rettighederne skal ændres for brugeren (fx `u+r`), for
  gruppen (`g+w`), for andre (`o-rwx`) eller for alle (`a+r`)

Den rigtige chmod-kommando kan lidt flere ting, fx at angive rettigheder for
flere af `u`, `g` og `o` samtidigt, samt angive flere rettighedsændringer
adskilt med komma, fx `u+rwx,go-rwx`. Det behøver vores version ikke kunne.

Brug struct'en fra forrige chmod-aflevering, hvor en bitmaske indeholder
rettighederne.

Du må selv bestemme om du bruger SDS strings eller C strings.

## Afprøvning

- **Sørg for at tilføje flere tests!**
- **Hvis du ved at din funktion fejler på et bestemt input, så lav en test der fejler.**