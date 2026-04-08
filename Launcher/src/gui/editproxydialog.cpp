#include "editproxydialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QMessageBox>
#include <QVBoxLayout>

EditProxyDialog::EditProxyDialog(QWidget* parent)
    : QDialog(parent)
{
    setWindowTitle("Edit proxy");
    setWindowFlag(Qt::WindowContextHelpButtonHint, false);

    useProxyCheckBox = new QCheckBox("Use SOCKS5 proxy", this);
    proxyIpLineEdit = new QLineEdit(this);
    socksPortLineEdit = new QLineEdit(this);
    proxyUsernameLineEdit = new QLineEdit(this);
    proxyPasswordLineEdit = new QLineEdit(this);

    proxyPasswordLineEdit->setEchoMode(QLineEdit::Password);

    QFormLayout* formLayout = new QFormLayout();
    formLayout->addRow(useProxyCheckBox);
    formLayout->addRow("Proxy IP:", proxyIpLineEdit);
    formLayout->addRow("Port:", socksPortLineEdit);
    formLayout->addRow("Username:", proxyUsernameLineEdit);
    formLayout->addRow("Password:", proxyPasswordLineEdit);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal,
        this
    );

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(buttonBox);
    setLayout(mainLayout);

    connect(useProxyCheckBox, &QCheckBox::toggled, this, &EditProxyDialog::updateProxyFieldsEnabled);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &EditProxyDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &EditProxyDialog::reject);

    updateProxyFieldsEnabled(false);
}

void EditProxyDialog::setValues(
    bool useProxyValue,
    const QString& ipValue,
    const QString& portValue,
    const QString& usernameValue,
    const QString& passwordValue
)
{
    useProxyCheckBox->setChecked(useProxyValue);
    proxyIpLineEdit->setText(ipValue);
    socksPortLineEdit->setText(portValue);
    proxyUsernameLineEdit->setText(usernameValue);
    proxyPasswordLineEdit->setText(passwordValue);
    updateProxyFieldsEnabled(useProxyValue);
}

bool EditProxyDialog::getUseProxy() const
{
    return useProxyCheckBox->isChecked();
}

QString EditProxyDialog::getProxyIp() const
{
    return proxyIpLineEdit->text();
}

QString EditProxyDialog::getSocksPort() const
{
    return socksPortLineEdit->text();
}

QString EditProxyDialog::getProxyUsername() const
{
    return proxyUsernameLineEdit->text();
}

QString EditProxyDialog::getProxyPassword() const
{
    return proxyPasswordLineEdit->text();
}

void EditProxyDialog::accept()
{
    if (getUseProxy() && (getProxyIp().trimmed().isEmpty() || getSocksPort().trimmed().isEmpty())) {
        QMessageBox::critical(this, "Error", "If proxy is enabled, IP and port are required.");
        return;
    }

    QDialog::accept();
}

void EditProxyDialog::updateProxyFieldsEnabled(bool enabled)
{
    proxyIpLineEdit->setEnabled(enabled);
    socksPortLineEdit->setEnabled(enabled);
    proxyUsernameLineEdit->setEnabled(enabled);
    proxyPasswordLineEdit->setEnabled(enabled);
}
