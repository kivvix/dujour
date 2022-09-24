# dujour

> time C++ portions

Dujour est aussi le nom du personnage joué par Ada Nicodemou dans Matrix, et possédant le tatouage de lapin blanc, faisant ainsi référence au lapin blanc d'Alice au pays des merveilles qu'Alice (ou Néo) suit, et qui l'emmènera dans le terrier. Ici on utilise la référence juste parce que ce lapin blanc est en retard et qu'il a rendez-vous quelque part.

# To do list:

* trouver un autre nom à un simple timer de scope

# Utilisation

```
{
  auto tmp = dujour::scope_timer<double>::start(__func__);

  // ... make something

}

// ...

for ( auto kv : dujour::scope_timer<double>::cumulative_times() ) {
  std::cout << kv.first << " "
            << kv.second.time.count() << " "
            << kv.second.count << "\n";
}
```

