////////////////////////////////////////////////////////////////////////////////
/// @file      CPhysicalDeviceManager.cpp
///
/// @author    Stephen Jackson <scj7t4@mst.edu>
///
/// @project   FREEDM DGI
///
/// @description
///     Handles access and distribution of physical devices.
///
/// @copyright
///     These source code files were created at Missouri University of Science
///     and Technology, and are intended for use in teaching or research. They
///     may be freely copied, modified, and redistributed as long as modified
///     versions are clearly marked as such and this notice is not removed.
///     Neither the authors nor Missouri S&T make any warranty, express or
///     implied, nor assume any legal responsibility for the accuracy,
///     completeness, or usefulness of these files or any information
///     distributed with these files. 
///     
///     Suggested modifications or questions about these files can be directed
///     to Dr. Bruce McMillin, Department of Computer Science, Missouri
///     University of Science and Technology, Rolla, MO 65409 <ff@mst.edu>.
////////////////////////////////////////////////////////////////////////////////

#include "device/CPhysicalDeviceManager.hpp"
#include "CLogger.hpp"

#include <boost/bind.hpp>

namespace freedm {
namespace broker {
namespace device {

static CLocalLogger Logger(__FILE__);

///////////////////////////////////////////////////////////////////////////////
/// @fn CPhysicalDeviceManager::CPhysicalDeviceManager()
/// @brief Constructor for the physical device manager
/// @pre None
/// @post PhysicalDeviceManager is ready to accept & distribute devices.
///////////////////////////////////////////////////////////////////////////////
CPhysicalDeviceManager::CPhysicalDeviceManager()
{
    //intentionally left blank
}

///////////////////////////////////////////////////////////////////////////////
/// @fn CPhysicalDeviceManager::AddDevice
/// @brief Registers a device with the physical device manager.
/// @pre The physical device manager is initialized
/// @post The device has been registered with the manager and is ready to
///       retrieve
/// @param resource a IPhysicalDevice::DevicePtr to the device.
///////////////////////////////////////////////////////////////////////////////
void CPhysicalDeviceManager::AddDevice(device::IDevice::DevicePtr resource)
{
    m_devices[resource->GetID()] = resource;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn CPhysicalDeviceManager::RemoveDevice
/// @brief Removes the registration of the device from the manager.
/// @pre The device in question has its identifier in the devices table
/// @post The device with the matching identifier is removed from the table.
/// @param devid The identifier which will be used to specify the device removed
///////////////////////////////////////////////////////////////////////////////
void CPhysicalDeviceManager::RemoveDevice(device::Identifier devid)
{
    m_devices.erase(devid);
}

///////////////////////////////////////////////////////////////////////////////
/// @fn CPhysicalDeviceManager::GetDevice
/// @brief Returns a shared ptr to the device specified
/// @pre The device in question is in the devices table
/// @post No change
/// @return A DevicePtr to the device, or NULL if the device wasn't found.
///////////////////////////////////////////////////////////////////////////////
device::IDevice::DevicePtr CPhysicalDeviceManager::GetDevice(
        device::Identifier devid)
{
    iterator di = m_devices.find(devid);
    if (di != m_devices.end())
    {
        return di->second;
    }
    else
    {
        return device::IDevice::DevicePtr();
    }
}

///////////////////////////////////////////////////////////////////////////////
/// @fn CPhysicalDeviceManager::DeviceExists
/// @brief Tests to see if the device exists in the devices table.
/// @pre The object is initialized.
/// @post No change.
/// @param devid The device to look for.
/// @return True if the device is in the device table, false otherwise
///////////////////////////////////////////////////////////////////////////////
bool CPhysicalDeviceManager::DeviceExists(device::Identifier devid) const
{
    if (m_devices.count(devid))
        return true;
    return false;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn CPhysicalDeviceManager::DeviceCount
/// @brief returns a count of the number of devices being tracked at the moment
/// @pre The object is initialized
/// @post No change.
/// @return The number of devices currently being tracked.
///////////////////////////////////////////////////////////////////////////////
size_t CPhysicalDeviceManager::DeviceCount() const
{
    return m_devices.size();
}

} // namespace device
} // namespace broker
} // namespace freedm
