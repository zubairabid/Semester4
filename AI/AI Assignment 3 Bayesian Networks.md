​                                                                                                                                                                                                        

```mermaid
graph TB

SS(Student Satisfaction)
FS(Faculty Satisfaction) 

CA(Cultural Activity)
PP(Placements)

AO(Academic Output)
RO(Research Output)

HH(Student Health)
FT(Free Time Available)


OA(0%)
OB(60%)
OC(85%)
OD(100%)

FS --> OA
FS --> OB
FS --> OC
FS --> OD

SS --> OA
SS --> OB
SS --> OC
SS --> OD

CA --> SS
RO --> SS
PP --> SS


AO --> FS
RO --> FS

FT --> AO
FT --> CA

HH --> AO
HH --> CA
HH --> RO
```

| Abbreviation | Node                 | Values                |
| ------------ | -------------------- | --------------------- |
| HH           | Student Health       | Good, Bad             |
| FT           | Free Time Available  | Less, Adequate, Extra |
| AO           | Academic Output      | Good, Poor            |
| RO           | Research Output      | Good, Decent          |
| CA           | Cultural Activity    | High, Low             |
| PP           | Placements           | High, Very High       |
| FS           | Faculty Satisfaction | Happy, Unhappy        |
| SS           | Student Satisfaction | Happy, Unhappy        |
| OA           | 0% Attendance        | Yes, No               |
| OB           | 60% Attendance       | Yes, No               |
| OC           | 85% Attendance       | Yes, No               |
| OD           | 100% Attendance      | Yes, No               |
