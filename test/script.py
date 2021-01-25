
a = ["b1c3", "b1a3", "d1e2", "e1e2", "e1f1", "h1g1", "h1f1", "a2a3", "a2a4", "b2b3", "b2b4", "c2c3", "c2c4", "d2d3",
     "d2d4", "g2g3", "g2g4", "h2h3", "h2h4", "f3g5", "f3h4", "f3g1", "f3d4", "f3e5", "b5c6", "b5c4", "b5d3", "b5e2",
     "b5f1", "b5a4", "b5a6"]

b = ["b5a6", "b5c4", "b5d3", "b5e2", "b5f1", "b5c6", "b5a4", "f3g5", "f3h4", "f3g1", "f3d4", "f3e5", "a2a3", "a2a4",
     "b2b3", "b2b4", "c2c3", "c2c4", "d2d3", "d2d4", "g2g3", "g2g4", "h2h3", "h2h4", "b1c3", "b1a3", "d1e2", "e1e2",
     "h1g1", "h1f1"]

print(len(a))
print(len(b))

for str in a:
    if not str in b:
        print(str)


