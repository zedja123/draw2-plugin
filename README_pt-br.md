<div align="center">
    <p>
        <img src="https://raw.githubusercontent.com/HichTala/draw2/refs/heads/main/figures/banner-draw.png">
    </p>


<div>

[![DRAW2 Workflow](https://github.com/HichTala/draw2-plugin/actions/workflows/push.yaml/badge.svg)](https://github.com/HichTala/draw2-plugin/actions/workflows/push.yaml)
[![Licence](https://img.shields.io/pypi/l/ultralytics)](LICENSE)
[![Github](https://img.shields.io/badge/-github-181717?logo=github&labelColor=555)](https://github.com/HichTala/draw2)
[![Twitter](https://img.shields.io/badge/-twitter-000?logo=x&labelColor=555)](https://twitter.com/hichtala)
[![HuggingFace Downloads](https://img.shields.io/badge/dynamic/json?url=https%3A%2F%2Fhuggingface.co%2Fapi%2Fmodels%2FHichTala%2Fdraw2&query=%24.downloads&logo=huggingface&label=downloads&color=%23FFD21E)](https://huggingface.co/HichTala/draw2)
[![Medium](https://img.shields.io/badge/-Medium-12100E?style=flat&logo=medium&labelColor=555)](https://medium.com/@hich.tala.phd/how-i-trained-again-my-model-to-detect-and-recognise-a-wide-range-of-yu-gi-oh-cards-5c567a320b0a)
[![WandB](https://img.shields.io/badge/visualize_in-W%26B-yellow?logo=weightsandbiases&color=%23FFBE00)](https://wandb.ai/hich_/draw)

[🇬🇧 English](README.md)/[🇫🇷 Français](README_fr.md)


</div>

</div>

DRAW 2 (que significa **D**etect and **R**ecognize **A** **W**ide range of cards version 2 - **D**etectar e **R**econhecer uma **A**mpla gama de cartas versão "**W**" 2) é um detector de objetos treinado para detectar cartas de _Yu-Gi-Oh!_ em todos os tipos de imagens e em particular, imagens de duelos.

Esse projeto é a parte do plugin do sistema DRAW 2. Ele permite usuários **sem nenhuma experiência técnica** a integrar perfeitamente o detector diretamente nas suas live streams ou vídeos gravados.
O plugin pode exibir cartas detectadas em tempo real para uma experiência de visualização elevada.
O projeto de backend está disponível [aqui](https://github.com/HichTala/draw2).

Esse projeto é licenciado sob [GNU Affero General Public License v3.0](LICENCE); qualquer contribuição é bem-vinda.

---

## <div align="center">Documentação</div>

### 🛠️ Instalação

Siga a instrução de instalação dependendo do seu sistema operacional para que tudo funcione perfeitamente:

<details open>
<summary>🪟 Windows</summary>

1. Baixe o instalador do plugin deste 
   link: [DRAW2 Plugin Installer](https://github.com/HichTala/draw2-plugin/releases/download/0.1.4/draw2-plugin-installer.exe)
2. Execute o instalador e siga as instruções na tela.
3. Assim que a instalação estiver concluída, execute o OBS Studio. Se tudo foi configurado corretamente, 
   deve-se ver no menu `Painéis` uma nova opção chamada `Draw 2`. 
   Você pode ativar o painel e colocá-lo onde quiser.
4. Nessa etapa, a instalação não está completa ainda. Você precisa baixar os "model weights" do DRAW 2.
   Feche o OBS Studio e abra a pasta onde o plugin está instalado. Por padrão, deve estar em: 
   `C:\Arquivos de Programas\draw2`. Aqui, abra a pasta `python`, clique com o botão direito em qualquer lugar dentro da pasta e selecione `Abrir no Terminal`.
5. No terminal, execute o seguinte comando para baixar os "model weights":
   ```bash
   ./python.exe -c "import draw;draw.run()"
   ```
6. Nessa etapa você deve ver alguns logs incluindo barras de progresso baixando os "model weights".
   Assim que você vir:
    ```bash
    Running Draw2 without OBS shared memory
    Waiting for OBS to start...
   ```
   o download foi concluído e você pode reabrir o OBS Studio.
</details>

<details>
<summary>🐧 Linux</summary>

Em Breve.™ 👀
</details>

<details>
<summary>🍏 MacOS</summary>

Não sou tão familiar com o OBS no MacOS para fornecer um guida de instalação confiável.
O plugin é capaz de compilar com sucesso no MacOS mas não testei ele completamente.
Se você tem experiência com plugins do OBS no MacOS e gostaria de contribuir com um guia de instalação, 
sinta-se livre para enviar um pull request.
</details>

### 🚀 Uso

Quando o plugin está instalado e os "model weights" estão baixados, você pode executar o OBS Studio.

1. Abra o menu `Painéis` e selecione `Draw 2` para ativar o painel do plugin.
2. No painel do Draw 2, você pode configurar os ajustes clicando no ícone de engrenagem ao lado do botão `Start DRAW`:
    - **Select Deck List**: Escolha o arquivo de decklist que contenha as cartas que você quer detectar. 3 decklists podem ser usadas ao mesmo tempo. 
      Para adicionar novas decklists, você pode clicar no botão `Open Folder` e arrastar suas decklists (em formato .ydk) na pasta que foi aberta.
    - **Minimum Out of Screen Time**: O tempo mínimo que uma carta recém detectada pode ser exibida de novo.
    - **Minimum Screen Time**: O tempo mínimo que uma carta é exibida.
    - **Confidence Threshold**: Definir o nível de confiança mínima para a detecção de uma carta. Detecções abaixo desse limite 
      serão ignoradas.
3. O plugin irá fornecer uma nova fonte chamada `Draw Display`. Você pode adicioná-la a sua cena como qualquer outra fonte.
   Essa fonte irá exibir as cartas detectadas na tela. Você pode escolher de qual fonte/cena detectar as cartas.
4. Clique no botão `Start DRAW` para começar o processo de detecção. O plugin irá começar a detectar cartas em tempo real
   e exibí-las na tela usando a fonte `Draw Display`. O plugin irá começar a detectar a partir do momento que você vir o botão `Stop DRAW`. 
   Se não aparecer, algo deu errado.
5. Dando tudo certo, aproveite o plugin!

Aqui está uma pequena prévia :)
<div align="center">
    <img src="https://raw.githubusercontent.com/HichTala/draw2/refs/heads/main/figures/overview.gif" width="960" height="540" />
</div>

---
## <div align="center">🔍Visão Geral do Método</div>

Um post de blog no Medium explicando o processo principal da coleta de dados até a previsão final foi escrita.
Você pode acessar ele [neste](https://medium.com/@hich.tala.phd/how-i-trained-again-my-model-to-detect-and-recognise-a-wide-range-of-yu-gi-oh-cards-5c567a320b0a) endereço. Se você tiver quaisquer perguntas, não hesite em abrir uma issue.

[![Medium](https://img.shields.io/badge/-Medium-12100E?style=flat&logo=medium&labelColor=555)](https://medium.com/@hich.tala.phd/how-i-trained-again-my-model-to-detect-and-recognise-a-wide-range-of-yu-gi-oh-cards-5c567a320b0a)

---

## <div align="center">Contato</div>

Você pode me contatar pelo X(Twitter) [@hichtala](https://twitter.com/hichtala) ou por e-mail [hich.tala.phd@gmail.com](mailto:hich.tala.phd@gmail.com).

---

## <div align="center">⭐Histórico de Estrelas</div>

<div align="center">
<a href="https://www.star-history.com/#hichtala/draw2&type=date&legend=top-left">
 <picture>
   <source media="(prefers-color-scheme: dark)" srcset="https://api.star-history.com/svg?repos=hichtala/draw2&type=date&theme=dark&legend=top-left" />
   <source media="(prefers-color-scheme: light)" srcset="https://api.star-history.com/svg?repos=hichtala/draw2&type=date&legend=top-left" />
   <img alt="Star History Chart" src="https://api.star-history.com/svg?repos=hichtala/draw2&type=date&legend=top-left" />
 </picture>
</a>
</div>
