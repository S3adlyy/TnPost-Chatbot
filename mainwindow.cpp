#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    userName = "";  // Initialize userName to empty

    // Initialize the timer
    responseTimer = new QTimer(this);
    responseTimer->setSingleShot(true);
    connect(responseTimer, &QTimer::timeout, this, &MainWindow::showResponse);

    // Connect the web button to the slot
    connect(ui->web, &QPushButton::clicked, this, &MainWindow::on_web_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_b1_clicked()
{
    QString userInput = ui->q1->text();

    // Clear previous chat in QTextEdit
    ui->txt->clear();

    QString lowerInput = userInput.toLower();

    // Personalized Greeting
    if (lowerInput.startsWith("my name is ")) {
        userName = lowerInput.mid(11); // Extract name
        botResponse = "Nice to meet you, " + userName + "!";
    } else if (lowerInput == "what is your name") {
        if (!userName.isEmpty()) {
            botResponse = "Your name is " + userName + ". How can I assist you today?";
        } else {
            botResponse = "I don't know your name yet. Please tell me by saying 'My name is...'";
        }
    } else if (lowerInput == "hey" || lowerInput == "bonjour") {
        botResponse = "Hello, how can I help you?";
    } else if (lowerInput == "how are you") {
        botResponse = "I'm fine, what about you :) ?";
    } else if (lowerInput == "what is your favorite food" || lowerInput == "favorite" || lowerInput == "do you love me") {
        botResponse = "I'm just an AI chatbot, I don't have feelings. I'm sorry.";
    } else if (lowerInput.contains("time")) {
        QTime time = QTime::currentTime();
        botResponse = "The current time is " + time.toString();
    } else if (lowerInput.contains("date")) {
        QDate date = QDate::currentDate();
        botResponse = "Today's date is " + date.toString();
    } else if (lowerInput.contains("weather")) {
        botResponse = "I can't check the weather for you, but you can look it up online.";
    } else if (lowerInput.contains("joke")) {
        botResponse = "Why don't scientists trust atoms? Because they make up everything!";
    } else if (lowerInput.contains("help")) {
        botResponse = "Sure, I can help! Ask me anything.";
    } else if (lowerInput.contains("fact")) {
        // Fun fact
        botResponse = "Did you know? Honey never spoils. Archaeologists have found pots of honey in ancient Egyptian tombs that are over 3000 years old and still perfectly edible.";
    } else if (lowerInput.contains("e-dinar") || lowerInput.contains("dinar electronique")) {
        botResponse = "DINAR ELECTRONIQUE: Il s'agit d'une monnaie électronique simple, entièrement sécurisée, permettant à son porteur d'effectuer des micro-paiements sur Internet où et quand il le désire, jour et nuit, 7 jours sur 7.\nwww.e-dinar.poste.tn";
    } else if (lowerInput.contains("mailpost")) {
        botResponse = "M@ILPOST: M@ilPost est le service de la Poste Tunisienne qui offre à tout citoyen une adresse électronique sécurisée, personnalisée et liée à l'adresse physique. Bien plus qu’un service de messagerie électronique, M@ilPost est une plateforme de services de communication innovante.\nwww.mailpost.tn";
    } else if (lowerInput.contains("ccpnet")) {
        botResponse = "CCPNET: Une gamme complète de services en ligne vous permettant de gérer quotidiennement vos comptes CCP et Epargne. Avec CCPNET, vous bénéficiez de services hautement sécurisés, simples et rapides.\nwww.ccpnet.poste.tn";
    } else if (lowerInput.contains("fatouranet")) {
        botResponse = "FATOURANET: Un service de consultation et de payement de vos factures en ligne : Eau, Téléphone, Electricité, …\nwww.fatouranet.poste.tn";
    } else if (lowerInput.contains("mandat e-dinar")) {
        botResponse = "MANDAT E-DINAR: Ce service vous permet d'envoyer un mandat d'un montant ne dépassant pas 250 DT et à concurrence de l'avoir disponible au niveau de votre compte virtuel e-dinar.\nwww.e-shop.poste.tn";
    } else if (lowerInput.contains("suivi de vos envois") || lowerInput.contains("rapid-poste")) {
        botResponse = "SUIVI DE VOS ENVOIS RAPID-POSTE: La Poste Tunisienne met à votre disposition un système de suivi électronique de vos envois confiés à Rapid-Poste. Vous pouvez obtenir à tout moment les informations utiles sur votre envoi.\nwww.e-suivi.poste.tn";
    } else if (lowerInput.contains("fleurs de la poste")) {
        botResponse = "FLEURS DE LA POSTE: Pour mieux vous servir, la Poste Tunisienne vous offre un service de livraison rapide: 'Fleurs de la Poste'. En quelques heures, notre service Rapid-Poste assure la livraison de votre commande à son destinataire.\nwww.e-fleurs.poste.tn";
    } else if (lowerInput.contains("boutique des timbres-poste")) {
        botResponse = "BOUTIQUE DES TIMBRES-POSTE: La boutique des timbres-poste de la Tunisie vous permet de commander en ligne les timbres et les produits philatéliques tunisiens.\nwww.e-stamps.poste.tn";
    } else if (lowerInput.contains("webtelegram")) {
        botResponse = "WEBTELEGRAM: Le service en ligne 'WebTelegram' vous permet, sans vous déplacer, d'envoyer vos télégrammes via Internet aux destinataires de votre choix résidant en Tunisie.\nwww.webtelegram.poste.tn";
    } else if (lowerInput.contains("tahani")) {
        botResponse = "TAHANI: Ce service vous permet d'envoyer via Internet des télégrammes de félicitation. La Poste Tunisienne procède à l'impression du texte du télégramme choisi, à son insertion dans une enveloppe spéciale et attrayante et assure sa distribution au destinataire dans des délais extrêmement réduits sur tout le territoire de la Tunisie.\nwww.webtelegram.poste.tn/Telegram/tahani/";
    } else if (lowerInput.contains("ecole virtuelle")) {
        botResponse = "ECOLE VIRTUELLE: La Poste Tunisienne a le plaisir de mettre à la disposition du personnel de la Poste une plate-forme de formation à distance via Internet qui s'inscrit dans le cadre de la diversification des mécanismes permettant l'amélioration des capacités humaines de l'entreprise d'une part et la multiplication des chances de promotion professionnelle d'autre part.\nwww.postelearning.poste.tn";
    } else if(lowerInput.contains("historique de la poste tunisienne")) {
        botResponse ="La Poste tunisienne (arabe : البريد التونسي), dénomination commerciale de l'Office national des Postes tunisiennes, est l'entreprise publique tunisienne de service postal. Depuis le 1er janvier 1999, à la suite du retrait des activités de téléphonie";
    } else {
        botResponse = "Sorry, I didn't understand that. Can you please rephrase?";
    }

    // Show loading message
    ui->txt->append("Bot is typing...");
    responseTimer->start(2000);  // 2 seconds delay
    ui->q1->clear();
}

void MainWindow::showResponse()
{
    // Remove the loading message
    ui->txt->clear();
    // Show the bot's response
    ui->txt->append("Bot: " + botResponse);
}

void MainWindow::on_web_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.poste.tn/"));
}

void MainWindow::on_ww_clicked()
{
    QUrl url("file:///C:/Users/LWES/Desktop/webpage%20chatbot/index.html");  // Path to your local HTML file
    QDesktopServices::openUrl(url);
}

void MainWindow::on_go_clicked()
{
    QUrl url("https://play.google.com/store/apps/details?id=tn.mobipost&hl=fr&pli=1");  // Path to your local HTML file
    QDesktopServices::openUrl(url);
}

void MainWindow::on_ap_clicked()
{
    QUrl url("https://apps.apple.com/tn/app/digipostbank-d17/id1475640303?l=fr-FR");  // Path to your local HTML file
    QDesktopServices::openUrl(url);
}

