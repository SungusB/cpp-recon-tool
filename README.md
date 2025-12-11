# C++ Recon Automation Tool

Ferramenta de CLI para escaneamento de portas TCP, desenvolvida em C++ moderno (C++17).

### Destaques Técnicos
A ferramenta foi construída sem dependências externas de rede (como Boost.Asio), utilizando apenas a API nativa do Linux (POSIX).
* **Performance:** Implementação de `ThreadPool` customizado para varredura paralela.
* **Low-Level Networking:** Uso de `sys/socket` com `fcntl` e `select` para conexões não-bloqueantes.
* **Concorrência Segura:** Uso de `std::mutex` e `std::lock_guard` para proteção de I/O (Thread Safety).

### Estrutura e Implementação
O código foi modularizado para separar a lógica de rede, concorrência e controle de fluxo.

| Componente | Arquivo | Detalhes da Implementação |
| :--- | :--- | :--- |
| **ThreadPool Engine** | `src/threadpool.cpp` | Gerenciador de workers usando `std::thread`, `std::queue` e `std::condition_variable` para distribuir tarefas eficientemente. |
| **Non-Blocking I/O** | `src/network.cpp` | Wrapper de socket que utiliza `O_NONBLOCK` e `select()` para implementar timeouts precisos em conexões TCP. |
| **Scanner Logic** | `src/scanner.cpp` | Orquestrador que define a estratégia de scan (Rápido vs Preciso) e gerencia a saída no terminal com Mutex. |
| **CLI Entrypoint** | `src/main.cpp` | Tratamento de argumentos e inicialização da engine de scan. |

### Como Compilar e Rodar

Este projeto utiliza **CMake** para build

**Compilação:**
```bash
mkdir build
cd build
cmake ..
make
```

**Rodar**
Modo de rodar deve seguir o formato ./recon MODO IP PORTA_INICIAL PORTA_FINAL

